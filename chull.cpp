/* 
References: https://cw.fel.cvut.cz/wiki/_media/misc/projects/oppa_oi_english/courses/ae4m39vg/lectures/05-convexhull-3d.pdf
*/

#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <limits>
#include <set>
// A utility file made for common utilities like I/O
#include "utils.h"
#include "chull.h"
using namespace std;

float max_lim = numeric_limits<float>::max();

int main(){
	// define file parameters
	string inp_filename = "CONVEX.IN";
	string out_filename = "CONVEX.OUT";
	vector<pair<float,pair<float,float>>> v_inp, v_out;

	// Take input from the file
	get_input(inp_filename, v_inp);
	// Run qhull algorithm to compute convex hull on n points and store the result in v_out 
	qhull(v_inp, v_out);

	// Output v_out to out_filename
	get_output(out_filename, v_out);
	return 0;
}

float distance_plane(vector<pair<float, pair<float, float>>> &face, pair<float,pair<float,float>> pt){
	// Find farthest point from this triangle to complete the base tetrahedron
	float a = (face[1].second.first-face[0].second.first)*(face[2].second.second - face[0].second.second) - (face[1].second.second-face[0].second.second)*(face[2].second.first - face[0].second.first);
	float b = (face[2].first-face[0].first)*(face[1].second.second - face[0].second.second) - (face[2].second.second-face[0].second.second)*(face[1].first - face[0].first);
	float c = (face[1].first-face[0].first)*(face[2].second.first - face[0].second.first) - (face[1].second.first-face[0].second.first)*(face[2].first - face[0].first);
	// This was equation of a plane as a(x-x0) + b(y-y0) + c(z-z0) = 0;
	float dist = abs(a*(pt.first - face[0].first) + b*(pt.second.first - face[0].second.first) + c*(pt.second.second - face[0].second.second));
	dist = dist/(sqrt(a*a+b*b+c*c));
	return dist;
}

float distance_line(pair<float,pair<float,float>> pt, pair<float,pair<float,float>> pt1, pair<float,pair<float,float>> pt2){
	// line vector
	float vx = pt2.first - pt1.first;
	float vy = pt2.second.first - pt1.second.first;
	float vz = pt2.second.second - pt1.second.second;
	float mag = sqrt(vx*vx + vy*vy + vz*vz);
	vx /= mag;
	vy /= mag;
	vz /= mag;
	// vector from pt1 to point
	float ptx = pt.first - pt1.first;
	float pty = pt.second.first - pt1.second.first;
	float ptz = pt.second.second - pt1.second.second;
	float ptmag_sq = ptx*ptx + pty*pty + ptz*ptz;
	// Dot product
	float dot = ptx*vx + pty*vy + ptz*vz;
	// Pythagoras
	float dist = sqrt(ptmag_sq - dot*dot);
	return dist;
}

void qhull(vector<pair<float,pair<float,float>>> &v_inp, vector<pair<float,pair<float,float>>> &v_out){
	// Finding a line with max separated end points along one of the axis
	float minX = v_inp[0].first; int minXInd = 0;
	float maxX = v_inp[0].first; int maxXInd = 0;
	float minY = v_inp[0].second.first; int minYInd = 0;
	float maxY = v_inp[0].second.first; int maxYInd = 0;
	float minZ = v_inp[0].second.first; int minZInd = 0;
	float maxZ = v_inp[0].second.first; int maxZInd = 0;

	float distX = 0, distY = 0, distZ = 0;
	for(int i = 0; i<v_inp.size() ; ++i){
		if(v_inp[i].first < minX){
			minX = v_inp[i].first;
			minXInd = i;
		}
		if(v_inp[i].first > maxX){
			maxX = v_inp[i].first;
			maxXInd = i;
		}
		if(v_inp[i].second.first < minY){
			minY = v_inp[i].second.first;
			minYInd = i;
		}
		if(v_inp[i].second.first > maxY){
			maxY = v_inp[i].second.first;
			maxYInd = i;
		}
		if(v_inp[i].second.second < minZ){
			minZ = v_inp[i].second.second;
			minZInd = i;
		}
		if(v_inp[i].second.second > maxZ){
			maxZ = v_inp[i].second.second;
			maxZInd = i;
		}	
	}
	distX = maxX - minX;
	distY = maxY - minY;
	distZ = maxZ - minZ;
	float maxInd = maxXInd;
	float minInd = minXInd;
	if((distZ >= distX) && (distZ >= distY)){
		maxInd = maxZInd;
		minInd = minZInd;
	} else if(distY >= distX){
		maxInd = maxYInd;
		minInd = minYInd;
	}

	// Finding a farthest point from this line
	float maxD = 0; int maxDInd = -1;
	for(int i = 0; i<v_inp.size(); ++i){
		float dist = distance_line(v_inp[i], v_inp[minInd], v_inp[maxInd]);
		if(dist > maxD){
			maxD = dist;
			maxDInd = i;
		}
	}

	// Making a face triangle
	vector<pair<float, pair<float, float>>> face, face1, face2, face3;
	face.push_back(v_inp[minInd]); face.push_back(v_inp[maxInd]); face.push_back(v_inp[maxDInd]);

	// Creating base tetrahedron
	float maxT = 0; int maxTInd = maxInd;
	for(int i = 0; i<v_inp.size(); ++i){
		float dist = distance_plane(face, v_inp[i]);
		if(dist >= maxT){
			maxT = dist;
			maxTInd = i;
		}
	}
	face1.push_back(v_inp[minInd]); face1.push_back(v_inp[maxInd]); face1.push_back(v_inp[maxTInd]);
	face2.push_back(v_inp[minInd]); face2.push_back(v_inp[maxDInd]); face2.push_back(v_inp[maxTInd]);
	face3.push_back(v_inp[maxDInd]); face3.push_back(v_inp[maxInd]); face3.push_back(v_inp[maxTInd]);
	
	// Defining polyhedron as a vector of faces
	vector<vector<pair<float, pair<float, float>>>> poly;
	poly.push_back(face);
	poly.push_back(face1);
	poly.push_back(face2);
	poly.push_back(face3);

	// chk_list is the global list of points in which I maintain what all points are left to be considered for convex hull
	// face list is list of points nearest to a face
	vector<pair<float, pair<float, float>>> chk_list;
	vector<float> dist_list;
	vector<vector<pair<float, pair<float, float>>>> face_list;
	for(int i = 0; i<v_inp.size(); i++){
		dist_list.push_back(max_lim);
		vector<pair<float, pair<float, float>>> temp;
		face_list.push_back(temp);
	}
	// Notice that this point will always lie inside the convex hull. It will help me decide the points insed the convex polygon at any given time
	float meanX = (v_inp[minInd].first + v_inp[maxInd].first + v_inp[maxTInd].first + v_inp[maxDInd].first)/4;
	float meanY = (v_inp[minInd].second.first + v_inp[maxInd].second.first + v_inp[maxTInd].second.first + v_inp[maxDInd].second.first)/4;
	float meanZ = (v_inp[minInd].second.second + v_inp[maxInd].second.second + v_inp[maxTInd].second.second + v_inp[maxDInd].second.second)/4;
	pair<float,pair<float, float>> mean_pt;
	mean_pt.first = meanX;
	mean_pt.second.first = meanY;
	mean_pt.second.second = meanZ;

	// Calculate points nearest to a face and add that in face list
	for(int j = 0; j<v_inp.size(); j++){
		for(int i = 0; i<4; i++){
			if(opp_side(poly[i], poly[i][0],v_inp[j],mean_pt)){
				face_list[i].push_back(v_inp[j]);
			}
		}
	}

	for(int i = 0; i<v_inp.size(); i++){
		chk_list.push_back(v_inp[i]);
	}

	// Send this to a recursion
	for(int i = 0; i<4; i++){
		if(face_list[i].size() > 0){
			recurse_poly(poly, chk_list, poly[i], face_list[i], mean_pt);
		}
	}

	// Insert the vertices of a poly in a set to remove repeated vertices
	set <pair<float, pair<float, float>>> my_points;
	for(int i = 0; i<poly.size(); i++){
		for(int j = 0; j<poly[i].size(); j++){
			my_points.insert(poly[i][j]);
		}
	}

	// Iterate on the set to get the final output
	set<pair<float, pair<float, float>>>::iterator it1;
	for (it1 = my_points.begin(); it1!=my_points.end();  ++it1){ 
        v_out.push_back(*it1);
	} 
}

void recurse_poly(vector<vector<pair<float, pair<float, float>>>> &poly, vector<pair<float, pair<float, float>>> &chk_list, vector<pair<float, pair<float, float>>> &face, vector<pair<float, pair<float, float>>> &face_pts, pair<float, pair<float, float>> &mean_pt){
	// Base case
	if(face_pts.size() <= 0){
		return;
	}
	// If this face is no longer in the convex hull, no need to recurse on it
	bool chk = false;
	for(int i = 0; i<poly.size(); i++){
		if(same_face(poly[i], face)){
			chk = true;
			break;
		}
	}
	if(!chk){
		return;
	}

	// finding the eye point for the plane
	float max_d = 0;
	int max_ind = -1;
	for(int i = 0; i<face_pts.size(); i++){
		float dist = distance_plane(face, face_pts[i]);
		if(dist >= max_d){
			max_d = dist;
			max_ind = i;
		}
	}
	vector<int> visible_faces;
	
	// This is a vector of edges. Edges are represented as a pair of triplets
	vector<pair<pair<float, pair<float, float>>,pair<float, pair<float, float>>>> horizon;
	
	// Fills the horizon edges in horizon and visible faces in visible_faces
	int val = get_horizon(-1, visible_faces, horizon, face, poly, mean_pt, face_pts[max_ind]);

	sort(visible_faces.begin(), visible_faces.end());
	// Removing visible faces from the poly hedron as they will no longer be a part of convex hull
	for(int i = 0; i<visible_faces.size(); i++){
		poly[visible_faces[i]].clear();
	}

	for(int i = poly.size()-1; i>=0; i--){
		if(poly[i].size() == 0){
			poly.erase(poly.begin() + i);	
		}
	}

	// adding new faces to polyhedron
	vector<vector<pair<float, pair<float, float>>>> new_poly;	
	int init_size = poly.size();
	for(int i = 0; i < horizon.size(); i++){
		vector<pair<float, pair<float, float>>> temp_face;
		temp_face.push_back(horizon[i].first);
		temp_face.push_back(horizon[i].second);
		temp_face.push_back(face_pts[max_ind]);
		poly.push_back(temp_face);
		new_poly.push_back(temp_face);
	}

	// Now we will be distributing all the points w.r.t nearest faces
	vector<float> dist_list;
	vector<vector<pair<float, pair<float, float>>>> face_list;
	for(int i = 0; i<chk_list.size(); i++){
		dist_list.push_back(max_lim);
		vector<pair<float, pair<float, float>>> temp;
		face_list.push_back(temp);
	}

	for(int j = 0; j<chk_list.size(); j++){
		for(int i = 0; i<poly.size(); i++){
			if(opp_side(poly[i], poly[i][0], chk_list[j], mean_pt)){
				face_list[i].push_back(chk_list[j]);
			}
		}
	}

	// Send this to a recursion
	for(int i = 0; i<new_poly.size(); i++){
		if(face_list[init_size + i].size() > 0){
			recurse_poly(poly, chk_list, new_poly[i], face_list[init_size + i], mean_pt);
		}
	}	
}

bool opp_side(vector<pair<float, pair<float, float>>>& poly, pair<float, pair<float, float>>& on_face_pt, pair<float, pair<float, float>> &pt, pair<float, pair<float, float>> &mean_pt){
	float a = (poly[1].second.first-poly[0].second.first)*(poly[2].second.second - poly[0].second.second) - (poly[1].second.second-poly[0].second.second)*(poly[2].second.first - poly[0].second.first);
	float b = (poly[2].first-poly[0].first)*(poly[1].second.second - poly[0].second.second) - (poly[2].second.second-poly[0].second.second)*(poly[1].first - poly[0].first);
	float c = (poly[1].first-poly[0].first)*(poly[2].second.first - poly[0].second.first) - (poly[1].second.first-poly[0].second.first)*(poly[2].first - poly[0].first);

	float val1 = a*(pt.first - poly[0].first) + b*(pt.second.first - poly[0].second.first) + c*(pt.second.second - poly[0].second.second);
	float val2 = a*(mean_pt.first - poly[0].first) + b*(mean_pt.second.first - poly[0].second.first) + c*(mean_pt.second.second - poly[0].second.second);

	float val3 = val1/(val2+0.0000000001);
	if(val3 >= 0){
		return false;
	}else{
		return true;
	}
}

bool same_point(pair<float, pair<float, float>> &pt1, pair<float, pair<float, float>> &pt2){	
	if(pt1.first > pt2.first-0.00000001 && pt1.first < pt2.first+0.00000001){		
		if(pt1.second.first > pt2.second.first-0.00000001 && pt1.second.first < pt2.second.first+0.00000001){
			if(pt1.second.second > pt2.second.second-0.00000001 && pt1.second.second < pt2.second.second+0.00000001){
				return true;
			}else{
				return false;
			}
		}else{
			return false;
		}
	}else{		
		return false;
	}
}

bool same_face(vector<pair<float, pair<float, float>>>& poly, vector<pair<float, pair<float, float>>>& face){
	if(same_point(poly[0], face[0])){
		if(same_point(poly[1], face[1])){
			if(same_point(poly[2], face[2])){
				return true;
			}else{
				return false;
			}
		}else if(same_point(poly[1], face[2])){
			if(same_point(poly[2], face[1])){
				return true;
			}else{
				return false;
			}
		}else{
			return false;
		}
	}else if(same_point(poly[0], face[1])){
		if(same_point(poly[1], face[2])){
			if(same_point(poly[2], face[0])){
				return true;
			}else{
				return false;
			}
		}else if(same_point(poly[1], face[0])){
			if(same_point(poly[2], face[2])){
				return true;
			}else{
				return false;
			}
		}else{
			return false;
		}
	}else if(same_point(poly[0], face[2])){
		if(same_point(poly[1], face[0])){
			if(same_point(poly[2], face[1])){
				return true;
			}else{
				return false;
			}
		}else if(same_point(poly[1], face[1])){
			if(same_point(poly[2], face[0])){
				return true;
			}else{
				return false;
			}
		}else{
			return false;
		}
	}else{
		return false;
	}
}

int get_horizon(int ind, vector <int> &visible_faces, vector<pair<pair<float, pair<float, float>>,pair<float, pair<float, float>>>> &horizon, vector<pair<float, pair<float, float>>> &face, vector<vector<pair<float, pair<float, float>>>> &poly, pair<float, pair<float, float>> &mean_pt, pair<float, pair<float, float>> &eye_pt){	
	if((distance_plane(face, eye_pt) > 0.00000001) && (opp_side(face, face[0], eye_pt, mean_pt) == true)){
		if(ind == -1){
			for(int i = 0; i<poly.size(); i++){
				if(same_face(poly[i], face)){
					ind = i;
					break;
				}
			}
		}

		visible_faces.push_back(ind);
		for(int i = 0; i<3; i++){
			vector<pair<float, pair<float, float>>> neigh;
			int index = get_neighbour(i, ind, poly, face, neigh);			
			bool in_visited = false;
			for(int j = 0; j<visible_faces.size(); j++){
				if(same_face(poly[visible_faces[j]], neigh)){
					in_visited = true;
					break;
				}
			}

			if(!in_visited){
				int val = get_horizon(index, visible_faces, horizon, neigh, poly, mean_pt, eye_pt);
				if(val == 0){
					pair<pair<float, pair<float, float>>,pair<float, pair<float, float>>> common_edge;
					bool temp = get_common_edge(face, neigh, common_edge);
					horizon.push_back(common_edge);
				}
			}
		}
		return 1;
	}else{
		return 0;
	}
}

bool get_common_edge(vector<pair<float, pair<float, float>>> &face, vector<pair<float, pair<float, float>>> &neigh, pair<pair<float, pair<float, float>>,pair<float, pair<float, float>>> &common_edge){
	if(same_point(neigh[0], face[0])){
		if(same_point(neigh[1], face[1])){
			common_edge = make_pair(neigh[0], neigh[1]);
		}else if(same_point(neigh[1], face[2])){
			common_edge = make_pair(neigh[0], neigh[1]);
		}else if(same_point(neigh[2], face[1])){
			common_edge = make_pair(neigh[0], neigh[2]);
		}else if(same_point(neigh[2], face[2])){
			common_edge = make_pair(neigh[0], neigh[2]);
		}else{
			return false;
		}
	}else if(same_point(neigh[0], face[1])){
		if(same_point(neigh[1], face[2])){
			common_edge = make_pair(neigh[0], neigh[1]);
		}else if(same_point(neigh[1], face[0])){
			common_edge = make_pair(neigh[0], neigh[1]);
		}else if(same_point(neigh[2], face[2])){
			common_edge = make_pair(neigh[0], neigh[2]);
		}else if(same_point(neigh[2], face[0])){
			common_edge = make_pair(neigh[0], neigh[2]);
		}else {
			return false;
		}
	}else if(same_point(neigh[0], face[2])){
		if(same_point(neigh[1], face[0])){
			common_edge = make_pair(neigh[0], neigh[1]);
		}else if(same_point(neigh[1], face[1])){
			common_edge = make_pair(neigh[0], neigh[1]);
		}else if(same_point(neigh[2], face[0])){
			common_edge = make_pair(neigh[0], neigh[2]);
		}else if(same_point(neigh[2], face[1])){
			common_edge = make_pair(neigh[0], neigh[2]);
		}else{
			return false;
		}
	}else{
		if(same_point(neigh[1], face[0])){
			if(same_point(neigh[2],face[1]) || same_point(neigh[2], face[2])){
				common_edge = make_pair(neigh[1], neigh[2]);	
			}else{
				return false;
			}
		}else if(same_point(neigh[1], face[1])){
			if(same_point(neigh[2],face[0]) || same_point(neigh[2], face[2])){
				common_edge = make_pair(neigh[1], neigh[2]);	
			}else{
				return false;
			}		
		}else if(same_point(neigh[1], face[2])){
			if(same_point(neigh[2],face[1]) || same_point(neigh[2], face[0])){
				common_edge = make_pair(neigh[1], neigh[2]);	
			}else{
				return false;
			}
		}else{
			return false;
		}
	}
	return true;
}

int get_neighbour(int i, int ind, vector<vector<pair<float, pair<float, float>>>> &poly, vector<pair<float, pair<float, float>>> &face, vector<pair<float, pair<float, float>>> &neigh){
	pair<pair<float, pair<float, float>>,pair<float, pair<float, float>>> temp_edge;
	vector<pair<float, pair<float, float>>> temp_face;
	temp_face.push_back(face[i]);
	temp_face.push_back(face[(i+1)%3]);
	temp_face.push_back(make_pair(max_lim, make_pair(max_lim,max_lim)));
	for(int k = 0; k<poly.size(); k++){
		if((same_face(poly[k],face) == false) && (get_common_edge(poly[k], temp_face, temp_edge) == true)){
			neigh = poly[k];
			return k;
		}
	}
	return -1;
}