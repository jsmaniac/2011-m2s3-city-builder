// get_z()
#include "roam.h"

// Positionne v à (xx,yy) et calcule z. Met ref_count à 0.
#define INIT_VERTEX(v,xx,yy) do { (v)->refCount=0; (v)->x=(xx); (v)->y=(yy); (v)->z=get_z((xx),(yy)); } while(0);

inline Vertex* use_vertex(Vertex* v) { v->refCount++; return v; }
inline void unuse_vertex(Vertex* v) { if (--(v->refCount) == 0) free(v); }

// ROTATE4(x,r) == x+r % 4
#define ROTATE4(x,r) ((x+r) & 3)

// L'ordre dans les tableaux est toujours {ne,se,so,no} ou bien {n,e,s,o}.
typedef enum QTQuadrant { QT_NE = 0, QT_SE = 1, QT_SO = 2, QT_NO = 3 } QTQuadrant;
typedef enum QTCardinal { QT_N = 0, QT_E = 1, QT_S = 2, QT_O = 3 } QTCardinal;

#define ROT_NE (ROTATE4(QT_NE, r))
#define ROT_SE (ROTATE4(QT_SE, r))
#define ROT_SO (ROTATE4(QT_SO, r))
#define ROT_NO (ROTATE4(QT_NO, r))

#define ROT_N (ROTATE4(QT_N, r))
#define ROT_E (ROTATE4(QT_E, r))
#define ROT_S (ROTATE4(QT_S, r))
#define ROT_O (ROTATE4(QT_O, r))

// QuadTree Node.
typedef struct QTNode {
	Vertex* center;
	Vertex* vertices[4];
	struct QTNode* children[4];
	struct QTNode* neighbors[4];
	// linked list across all nodes, for traversal when we display them.
	struct QTNode* nextNode;
	struct QTNode* previousNode;
	unsigned int minLOD;
	unsigned int maxLOD;
} QTNode;

static inline void vertex_link_create(Vertex* a, Vertex* b, QTCardinal directionAB) {
	if (a != NULL) a->next[directionAB] = b;
	if (b != NULL) b->next[ROTATE4(directionAB, 2)] = a;
}

static inline void vertex_link_between(Vertex* vnew, Vertex* a, Vertex* b, QTCardinal directionAB) {
	vertex_link_create(a, vnew, directionAB);
	vertex_link_create(vnew, b, directionAB);
}

static inline void vertex_link_remove(Vertex* v) {
	vertex_link_create(v->next[QT_S], v->next[QT_N], QT_N);
	vertex_link_create(v->next[QT_O], v->next[QT_E], QT_E);
}

static inline void qtnode_link_create(QTNode* a, QTNode* b) {
	if (a != NULL) a->nextNode = b;
	if (b != NULL) b->previousNode = a;
}

void QT_split(QTNode* parent) {
	// Ne pas split un noeud déjà split.
	if (parent->children[QT_NE] != NULL) return;
	
	int r;
	QTNode* q[4];
	for (r = 0; r < 4; r++) {
		q[ROT_NE] = malloc(sizeof(QTNode));
	}
	
	Vertex* new_vertices[4];
	for (r = 0; r < 4; r++) {
		// réutiliser le vertex existant (parent->top_neighbor->se_child->so ou bien parent->top_neighbor->so_child->se)
		if (parent->neighbors[ROT_N] != NULL && parent->neighbors[ROT_N]->children[ROT_SE] != NULL) {
			new_vertices[ROT_N] = parent->neighbors[ROT_N]->children[ROT_SE]->vertices[ROT_SO];
		} else {
			new_vertices[ROT_N] = (Vertex*)malloc(sizeof(Vertex));
			// Insère le nouveau vertex entre les deux coins de parent.
			vertex_link_between(new_vertices[ROT_N], parent->vertices[ROT_NO], parent->vertices[ROT_NE], ROT_N);
			// place le nouveau vertex après center.
			vertex_link_create(parent->center, new_vertices[ROT_N], ROT_N);
			// Définit x,y,z et ref_count.
			switch (r) { // TODO : Devrait être factorisé.
				case 0: INIT_VERTEX(new_vertices[0], parent->center->x, parent->vertices[QT_NE]->y); break;
				case 1: INIT_VERTEX(new_vertices[1], parent->vertices[QT_SE]->x, parent->center->y); break;
				case 2: INIT_VERTEX(new_vertices[2], parent->center->x, parent->vertices[QT_SO]->y); break;
				case 3: INIT_VERTEX(new_vertices[3], parent->vertices[QT_NO]->x, parent->center->y); break;
			}
		}
	}
	
	for (r = 0; r < 4; r++) { // Dans le corps de la boucle, positions pour le quadrant ne.
		q[ROT_NE]->center = malloc(sizeof(Vertex));
		// Pas besoin d'insérer center dans une des listes : à sa création il ne sera accédé dans aucun parcours de périmètre.
		// Coordonnées du centre de qne = moyenne du center et de parent->vertices[QT_NE].
		INIT_VERTEX(q[ROT_NE]->center, (parent->center->x + parent->vertices[ROT_NE]->x) / 2, (parent->center->y + parent->vertices[ROT_NE]->y) / 2);
		use_vertex(q[ROT_NE]->center);
		
		q[ROT_NE]->vertices[ROT_NE] = use_vertex(parent->vertices[ROT_NE]);
		q[ROT_NE]->vertices[ROT_SE] = use_vertex(new_vertices[ROT_E]);
		q[ROT_NE]->vertices[ROT_SO] = use_vertex(parent->center);
		q[ROT_NE]->vertices[ROT_NO] = use_vertex(new_vertices[ROT_N]);

		q[ROT_NE]->children[ROT_NE] = NULL;
		q[ROT_NE]->children[ROT_SE] = NULL;
		q[ROT_NE]->children[ROT_SO] = NULL;
		q[ROT_NE]->children[ROT_NO] = NULL;

		// Si le voisin du haut de parent a un se_child, c'est le voisin du haut de qne.
		if (parent->neighbors[ROT_N] != NULL) {
			q[ROT_NE]->neighbors[ROT_N] = parent->neighbors[ROT_N]->children[ROT_SE];
			if (parent->neighbors[ROT_N]->children[ROT_SE] != NULL)
				parent->neighbors[ROT_N]->children[ROT_SE]->neighbors[ROT_S] = q[ROT_NE];
		} else {
			q[ROT_NE]->neighbors[ROT_N] = NULL;
		}
		// Si le voisin de droite de parent a un no_child, c'est le voisin de droite de qne.
		if (parent->neighbors[ROT_E] != NULL) {
			q[ROT_NE]->neighbors[ROT_E] = parent->neighbors[ROT_E]->children[ROT_NO];
			if (parent->neighbors[ROT_E]->children[ROT_NO] != NULL)
				parent->neighbors[ROT_E]->children[ROT_NO]->neighbors[ROT_O] = q[ROT_NE];
		} else {
			q[ROT_NE]->neighbors[ROT_E] = NULL;
		}
		q[ROT_NE]->neighbors[ROT_S] = q[ROT_SE];
		q[ROT_NE]->neighbors[ROT_O] = q[ROT_NO];
		
		parent->children[ROT_NE] = q[ROT_NE];
	}
	
	// remplacer parent par ses quatre enfants dans la liste d'énumération de tous les QTNode feuilles.
	qtnode_link_create(parent->previousNode, q[QT_NO]);
	qtnode_link_create(q[QT_NO], q[QT_NE]);
	qtnode_link_create(q[QT_NE], q[QT_SE]);
	qtnode_link_create(q[QT_SE], q[QT_SO]);
	qtnode_link_create(q[QT_SO], parent->nextNode);

	// TODO : set minLOD = maxLOD = parent->LOD + 1; // À moins que ça soit le parcours récursif de màj du mesh qui écrive cette information ?
}

void QT_merge(QTNode* parent) {
	// Ne pas merge un noeud sans enfants.
	if (parent->children[QT_NE] == NULL) return;
	
	qtnode_link_create(parent->children[QT_NO]->previousNode, parent);
	qtnode_link_create(parent, parent->children[QT_SO]->nextNode);
	
	int r;
	for (r = 0; r < 4; r++) {
		// Merge récursif des enfants.
		QT_merge(parent->children[ROT_NE]);
		
		// Supprime les vertex NESO de parent des listes de parcours.
		vertex_link_remove(parent->children[ROT_NE]->vertices[ROT_NO]);
		
		// reset à NULL les voisins qui pointaient vers des enfants.
		if (parent->neighbors[ROT_N] != NULL)
			if (parent->neighbors[ROT_N]->children[ROT_SE] != NULL)
				parent->neighbors[ROT_N]->children[ROT_SE]->neighbors[ROT_S] = NULL;
		if (parent->neighbors[ROT_E] != NULL)
			if (parent->neighbors[ROT_E]->children[ROT_NO] != NULL)
				parent->neighbors[ROT_E]->children[ROT_NO]->neighbors[ROT_O] = NULL;

		unuse_vertex(parent->children[ROT_NE]->center);
		int i;
		for (i = 0; i < 4; i++)
			unuse_vertex(parent->children[ROT_NE]->vertices[i]);
		
		free(parent->children[ROT_NE]);
		parent->children[ROT_NE] = NULL;
	}
}

QTNode* QT_baseNode() {
	QTNode* q = malloc(sizeof(QTNode));
	Vertex** v = malloc(sizeof(Vertex)*5);
	int i;

	vertex_link_create(v[1], v[2], QT_E);
	vertex_link_create(v[2], v[3], QT_S);
	vertex_link_create(v[3], v[4], QT_O);
	vertex_link_create(v[4], v[1], QT_N);
	
	INIT_VERTEX(v[0], 0, 0);
	INIT_VERTEX(v[1], +1024, +1024);
	INIT_VERTEX(v[2], +1024, -1024);
	INIT_VERTEX(v[3], -1024, -1024);
	INIT_VERTEX(v[4], -1024, +1024);
	
	q->center = use_vertex(v[0]);

	for (i = 0; i < 4; i++) {
		q->vertices[i] = use_vertex(v[i+1]);
		q->children[i] = NULL;
		q->neighbors[i] = NULL;
	}

	qtnode_link_create(q, NULL);
	qtnode_link_create(NULL, q);
	
	q->minLOD = 0;
	q->maxLOD = 0;
	
	return q;
}

QTNode* QT_example() {
	QTNode* q = QT_baseNode();
	return q;
}
