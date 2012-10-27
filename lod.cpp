#include "all_includes.hh"

Lod::Lod(Vertex _camera, Chose* root) {
	for (int i = 0; i < 6; i++) {
		merge[i].init((i & 1) ? 1 : -1);
		splitIn[i].init((i & 1) ? 1 : -1);
		splitOut[i].init((i & 1) ? -1 : 1);
	}
	this->camera[0] = _camera.x;
	this->camera[1] = _camera.y;
	this->camera[2] = _camera.z;
	addSplitCube(root);
	setCamera(_camera);
}

int debug_printlod_axis;

void Lod::setCamera(Vertex newCamera) {
	this->camera[0] = newCamera.x;
	this->camera[1] = newCamera.y;
	this->camera[2] = newCamera.z;

	// Merge.
	for(int i = 0; i < 6; i++) {
		Chose* c;
		while((c = merge[i].popIfLessThan(camera[i>>1]))) {
			for(int j = 0; j < 6; j++) {
				if(i == j) continue;
				merge[j].remove(c->lod.mergeBox[j], c);
			}
			doMerge(c);
		}
	}
	// Split out vers split in.
	for(int i = 0; i < 6; i++) {
		Chose* c;
		while((c = splitOut[i].popIfLessThan(camera[i>>1]))) {
			if(c->lod.inCounter == 5) {
				for(int j = 0; j < 6; j++) {
					if(i == j) continue;
					splitIn[j].remove(c->lod.splitBox[j], c);
				}
				doSplit(c);
			}
			else {
				c->lod.inCounter++;
				splitIn[i].insert(c->lod.splitBox[i], c);
			}
		}
	}

	// Split in vers split out.
	for(int i = 0; i < 6; i++) {
		Chose* c;
		while((c = splitIn[i].popIfLessThan(camera[i>>1]))) {
			c->lod.inCounter--;
			splitOut[i].insert(c->lod.splitBox[i], c);
		}
	}
	// Statistics
	Heap* heaps[3] = { merge, splitIn, splitOut };
	const char* heapNames[3] = { "merge", "splitIn", "splitOut" };
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 3; j++) {
			debug_printlod_axis = i/2;
			std::cout << "set term png" << std::endl
					  << "set output 'png/"
					  << heapNames[j] << " " << ((i & 1) ? '+' : '-') << (char)('x' + debug_printlod_axis) << " frame " << std::setfill('0') << std::setw(5) << Camera::debug_frame
					  << ".png'" << std::endl
					  << "unset arrow" << std::endl
					  << "set arrow from "
					  << camera[debug_printlod_axis] << "," << 0 <<" to "
					  << (camera[debug_printlod_axis] + 10000000*((i & 1) ? -1 : 1)) << "," << 10000000*(Dimensions::splitFactor)
					  << " nohead linecolor rgb 'blue'" << std::endl
					  << "plot '-' title '"
					  << heapNames[j] << " " << ((i & 1) ? '+' : '-') << (char)('x' + debug_printlod_axis) << " frame " << std::setfill('0') << std::setw(5) << Camera::debug_frame
					  << "' with dots linecolor variable" << std::endl
					  << "0, 0, 0" << std::endl
					  << heaps[j][i]
					  << "end" << std::endl;
		}
		// std::cout << "merge[" << i << "] = {" << merge[i] << "}" << std::endl;
		// std::cout << "splitIn[" << i << "] = {" << splitIn[i] << "}" << std::endl;
		// std::cout << "splitOut[" << i << "] = {" << splitOut[i] << "}" << std::endl;
	}
}

void Lod::doSplit(Chose* c) {
	c->split();
	std::vector<Chose*>::iterator it;
	bool mergeCube = false;
	for (it = c->children.begin(); it != c->children.end(); ++it) {
		mergeCube = true;
		(*it)->triangulation();
		(*it)->updateAABB();
		// (*it)->drawAABB();
		addSplitCube((*it));
	}
	addMergeCube(c);
	// else {
	// 	// Pour debug : quand on tente de split un objet qui ne peut
	// 	// pas l'être, on vire le dessin de sa splitBox.
	// 	c->clearTriangles();
	// 	c->triangulation();
	// }
}

void Lod::doMerge(Chose* c) {
	doSubMerge(c);
	addSplitCube(c);
}

void Lod::doSubMerge(Chose* c) {
	std::vector<Chose*>::iterator it;
	for (it = c->children.begin(); it != c->children.end(); ++it) {
		for(int j = 0; j < 6; j++) {
			merge[j].remove((*it)->lod.mergeBox[j], (*it));
			splitIn[j].remove((*it)->lod.splitBox[j], (*it));
			splitOut[j].remove((*it)->lod.splitBox[j], (*it));
		}
		doSubMerge(*it);
	}
	c->merge();
}

void Lod::addMergeCube(Chose* chose) {
	// Innutile de détecter si l'on est déjà sortis de la mergeBox :
	// comme elle est plus grosse que la splitBox, on est forcément
	// dedans.
	for(int i = 0; i < 6; i++)
		merge[i].insert(chose->lod.mergeBox[i], chose);
}

void Lod::addSplitCube(Chose* c) {
	c->lod.inCounter = 0;
	for(int i = 0; i < 6; i++) {
		if(splitOut[i].lessThan(c->lod.splitBox[i], camera[i>>1])) {
			c->lod.inCounter++;
			splitIn[i].insert(c->lod.splitBox[i], c);
		} else {
			splitOut[i].insert(c->lod.splitBox[i], c);
		}
	}
	if (c->lod.inCounter == 6) {
		for(int i = 0; i < 6; i++)
			splitIn[i].remove(c->lod.splitBox[i], c);
		doSplit(c);
	}
}
