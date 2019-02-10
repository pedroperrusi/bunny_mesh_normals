#%% [markdown]
#  # Visualize Bunny Mesh
# 
# Simple ipython notebook module to visualize numpy data.

#%% Change working directory from the workspace root to the ipynb file location. Turn this addition off with the DataScience.changeDirOnImportExport setting
#%%
# Initial setup ----------------------------------
import os
import numpy as np
try:
	os.chdir(os.path.join(os.getcwd(), 'python'))
	print(os.getcwd())
except:
	pass

os.chdir('../data') # change path to data folder

#%% Load and print the input data
bunny_faces = np.load('bunny_faces.npy')
bunny_vertices = np.load('bunny_vertices.npy')

# Get to know the data --------------------------
print('Bunny Faces :\n', bunny_faces,
      '\n\tShape : ', bunny_faces.shape)

print('Bunny Vertices :\n', bunny_vertices,
      '\n\tShape : ', bunny_vertices.shape)

#%% Load and print the output data

#%% Load and print the input data
faces_normals = np.load('face_normals.npy')
vertex_normals = np.load('vertex_normals.npy')

# Get to know the data --------------------------
print('Bunny Faces :\n', faces_normals,
      '\n\tShape : ', faces_normals.shape)

print('Bunny Vertices :\n', vertex_normals,
      '\n\tShape : ', vertex_normals.shape)