#ifndef CHULL_H
#define	CHULL_H

#include <vector>
#include <utility>
#include <string>
using namespace std;


/**
 * Function to check if there exist a common edge between 2 faces. If, yes what are they.
 * 
 * @param i edge number against which neighbour is searched
 * @param ind face index in poly
 * @param neigh face to get
 * @param face face in consideration
 */
int get_neighbour(int i, int ind, vector<vector<pair<float, pair<float, float>>>> &poly, vector<pair<float, pair<float, float>>> &face, vector<pair<float, pair<float, float>>> &neigh);

/**
 * Function to check if there exist a common edge between 2 faces. If, yes what are they.
 * 
 * @param neigh face 1
 * @param face face 2
 * @param common_edge return common edge found in this
 */
bool get_common_edge(vector<pair<float, pair<float, float>>> &face, vector<pair<float, pair<float, float>>> &neigh, pair<pair<float, pair<float, float>>,pair<float, pair<float, float>>> &common_edge);

/**
 * Function to see if 2 points are same or not.
 * 
 * @param pt1 point 1
 * @param pt2 point 2
 */
bool same_point(pair<float, pair<float, float>> &pt1, pair<float, pair<float, float>> &pt2);

/**
 * Function to get horizon of the visible portion of the polyhedron.
 * 
 * @param ind index of face in polyhedron. -1 if not known
 * @param poly current polyhedron
 * @param horizon edges to return
 * @param face current triangle face in consideration
 * @param visible_faces faces that are visible from eye
 * @param mean_pt a special point that always stays inside my partially complete polyhedron
 * @param eye_pt a point that is farthest from plane
 */
int get_horizon(int ind, vector <int> &visible_faces, vector<pair<pair<float, pair<float, float>>,pair<float, pair<float, float>>>> &horizon, vector<pair<float, pair<float, float>>> &face, vector<vector<pair<float, pair<float, float>>>> &poly, pair<float, pair<float, float>> &mean_pt, pair<float, pair<float, float>> &eye_pt);

/**
 * Function to see if 2 planes are same or not.
 * 
 * @param poly face 1
 * @param face face 2
 */
bool same_face(vector<pair<float, pair<float, float>>>& poly, vector<pair<float, pair<float, float>>>& face);

/**
 * Function to see if a point is inside or outside the polyhedron.
 * 
 * @param poly current face
 * @param on_face_pt a point on the face
 * @param pt point in consideration
 * @param mean_pt a special point that always stays inside my partially complete polyhedron
 */
bool opp_side(vector<pair<float, pair<float, float>>>& poly, pair<float, pair<float, float>>& on_face_pt, pair<float, pair<float, float>> &pt, pair<float, pair<float, float>> &mean_pt);

/**
 * Recursive Function to take a face and set of points to find the final polyhedron on that part of the space.
 * 
 * @param poly current polyhedron
 * @param chk_list current list of vertices left to consider
 * @param face current triangle face in consideration
 * @param face_list current list of vertices nearest to this face
 * @param mean_pt a special point that always stays inside my partially complete polyhedron
 */
void recurse_poly(vector<vector<pair<float, pair<float, float>>>> &poly, vector<pair<float, pair<float, float>>> &chk_list, vector<pair<float, pair<float, float>>> &face, vector<pair<float, pair<float, float>>> &face_pts, pair<float, pair<float, float>> &mean_pt);

/**
 * Function to find the convex hull using quickhull. The result is stored in v_out vector.
 * 
 * @param v_inp vector as initial set of points
 * @param v_out vector as final set of points in the convex hull
 */
void qhull(vector<pair<float,pair<float,float>>> &v_inp, vector<pair<float,pair<float,float>>> &v_out);

/**
 * Function to find the distance between a point and a line. The result is returned.
 * 
 * @param pt whose distance has to be found
 * @param pt1 one end point of a line
 * @param pt2 other end point of a line
 */
float distance_line(pair<float,pair<float,float>> pt, pair<float,pair<float,float>> pt1, pair<float,pair<float,float>> pt2);

/**
 * Function to find the distance between a point and a plane. The result is returned.
 * 
 * @param face list of points on a face
 * @param pt point whose distance we want
 */
float distance_plane(vector<pair<float, pair<float, float>>> &face, pair<float,pair<float,float>> pt);

#endif	/* CHULL_H */