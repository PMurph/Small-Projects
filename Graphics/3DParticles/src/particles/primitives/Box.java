package particles.primitives;

import java.util.ArrayList;

import javax.media.opengl.GL2;

import particles.ParticleCanvas;
import particles.materials.Material;
import particles.materials.SimpleColourMaterial;

public class Box implements Model {
	
	private ArrayList<float[]> vertices;
	private ArrayList<int[][]> faces;
	private ArrayList<Material> materials;
	
	public Box()
	{
		initBox();
	}
	
	public void draw(GL2 gl) {
		for(int[][] face: faces)
		{
			
		}
	}
	
	public void drawOutline(GL2 gl) {
		
	}
	
	private void drawFace(GL2 gl, int[] faceVertices, Material mat)
	{
		mat.setMaterial(gl);
		
		
		
		mat.unsetMaterials(gl);
	}

	private void initBox()
	{
		vertices = new ArrayList<float[]>();
		faces = new ArrayList<int[][]>();
		materials = new ArrayList<Material>();
		
		//Specify the box's vertices
		initVertices();
		
		//Specify the box's faces
		initFaces();
		
		initFaceColours();
	}
	
	private void initVertices()
	{
		vertices.add(new float[] { 0, 0, 0 });
		vertices.add(new float[] { 0, 0, -1 });
		vertices.add(new float[] { 1, 0, -1 });
		vertices.add(new float[] { 1, 0, 0 });
		vertices.add(new float[] { 0, 1, 0 });
		vertices.add(new float[] { 0, 1, -1 });
		vertices.add(new float[] { 1, 1, -1 });
		vertices.add(new float[] { 1, 1, 0 });
	}
	
	private void initFaces() {
		faces.add(new int[][] { {0, 1, 2}, {0} });
		faces.add(new int[][] { {0, 2, 3}, {0} });
		faces.add(new int[][] { {0, 3, 4}, {0} });
		faces.add(new int[][] { {3, 7, 4},  {0} });
		faces.add(new int[][] { {3, 2, 7}, {0} });
		faces.add(new int[][] { {2, 6, 7}, {0} });
		faces.add(new int[][] { {2, 1, 6}, {0} });
		faces.add(new int[][] { {1, 5, 6}, {0} });
		faces.add(new int[][] { {1, 5, 0}, {0} });
		faces.add(new int[][] { {0, 5, 4}, {0} });
		faces.add(new int[][] { {4, 6, 7}, {0} });
		faces.add(new int[][] { {4, 6, 5}, {0} });
	}
	
	private void initFaceColours()
	{
		Material faceMaterial = new SimpleColourMaterial(ParticleCanvas.DEFUALT_FACE_COLOUR);
		
		materials.add(faceMaterial);
	}
	
}
