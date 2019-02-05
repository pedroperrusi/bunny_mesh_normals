<!-- File written accondingly to GitHub markdown -->
# Bunny Mesh Normals

Ladies and gentlemen, I would like to introduce you the famous [Stanford Bunny][wiki_bunny] Triangle Mesh. If you would like to get to know him better, Georgia Tech provides an [overview][bunny_story] of his history and Stanford shares [his data source][Stanford_Source] and many other 3D models.

## The Challenge

Given the mesh data of the Stanford bunny, saved in the numpy format, the challenge is to develop a C++ program that computes:

1 - Normalized normals at each face of the object;

2 - Normalized normals at each vertex of the object.

## Dependencies

* [ZLIB](https://www.zlib.net)

* [Eigen](http://eigen.tuxfamily.org/)


<!-- References -->
[wiki_bunny]: https://en.wikipedia.org/wiki/Stanford_bunny
[bunny_story]: https://www.cc.gatech.edu/~turk/bunny/bunny.html
[Stanford_Source]: http://graphics.stanford.edu/data/3Dscanrep/