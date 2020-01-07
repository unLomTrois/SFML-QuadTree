template<typename T>
qt::node<T>::node(float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}

template<typename T>
qt::node<T>::node(T &p, float w, float h) : x(p.x), y(p.y), w(w), h(h) {}

template<typename T>
bool qt::node<T>::containsPoint(T &p){
	if ((p.x >= x - w) && (p.y >= y - h) &&
		(p.x <= x + w) && (p.y <= y + h)) {
		return true;
	} else {
		return false;
	}
}

template<typename T>
bool qt::node<T>::intersectNode(node node){
	return !(
		node.x - node.w > x + w || 
		node.x + node.w < x - w ||
		node.y - node.h > y + h ||
		node.y + node.h < y - h
	);
}