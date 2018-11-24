# Convex-Hull
Convex hull of given 3D points

# Method

There is a method named [Quickhull](https://en.wikipedia.org/wiki/Quickhull). The steps are mentioned in the wikipedia page.

# Algorithm

The main steps are as follows.

1) Make the initial tetrahedron which will serve as base. For this initially calculate the maximum and minimum points on all the axes.
	From this choose the 2 most farthest point and join a line.	Then find the point with maximum distance from this line and make a triangle.
	Then find most distant point from this plane and make a tetrahedron.

2) Divide the points to the 4 faces of the tetrahedron so that the points are outside of each faces. This can be done by checking whether a particular point lies at the same side as an internal point for all faces.

3) If the distance between such points is positive add the point to the to_do list of the vertex and remove it from the original list of the problem.

4) After doing this for all the 4 faces if the points that are still in the original list are the points which are inside the tetrahedron so neglet them. This process will be used in subsequent steps to eliminate the internal points.

5) After this we continue the program till there is a face that have non-zero vertices assigned to it.

6) For every face find the most distant point by step 2 and 3. Then we need to find the horizon of this point i.e – the vertices to which this point will connect.

7) A DFS from the face to which the point was a to_do list point. The continuation of the DFS depends on either the point in consideration is to_do list of the face. This will give me the final set of edges which are the horizon set.

8) The other vertices of the to_do list needs to be re assigned to the new faces of the cone that is made.

9) Do this for all the faces till any points are left.

# Usage
 - **gcc chull.cpp utils.cpp -o main** to generate the output binary as main.
 - **./ main** to execute the binary.Filename has been assumed to be CONVEX.IN and CONVEX.out for now.
    
# References
 - http://box2d.org/files/GDC2014/DirkGregorius_ImplementingQuickHull.pdf
 - https://cw.fel.cvut.cz/wiki/_media/misc/projects/oppa_oi_english/courses/ae4m39vg/lectures/05-convexhull-3d.pdf
 - https://en.wikipedia.org/wiki/Quickhull
