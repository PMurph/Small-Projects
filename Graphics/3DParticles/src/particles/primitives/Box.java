package particles.primitives;

import java.util.ArrayList;

import javax.media.opengl.GL2;

import particles.ParticleCanvas;
import particles.materials.DefaultOutlineMaterial;
import particles.materials.Material;
import particles.materials.SimpleColourMaterial;
import particles.transformations.Transformation;
import particles.transformations.TranslationTransformation;

public class Box implements Model {
	
	private ArrayList<float[]> vertices;
	private ArrayList<int[][]> faces;
	private ArrayList<Material> materials;
	private Transformation modelTransform;
	private float x, y, z;
	
	public Box()
	{
		modelTransform = null;
		
		initBox();
	}
	
	public Box(float x, float y, float z)
	{
		this.x = x;
		this.y = y;
		this.z = z;
		
		modelTransform = new TranslationTransformation(x, y, z);
		
		initBox();
	}
	
	public Box(Transformation modelTransformation)
	{
		this.modelTransform = modelTransformation;
		
		initBox();
	}
	
	public void draw(GL2 gl) {
		Material faceMaterial;
		
		if(modelTransform != null)
		{
			gl.glPushMatrix();
			modelTransform.transform(gl);
		}
			
		for(int[][] face: faces)
		{
			faceMaterial = materials.get(face[1][0]);
			
			faceMaterial.setMaterial(gl);
			
			gl.glBegin(GL2.GL_TRIANGLES);
			
			drawFace(gl, face[0]);
			
			gl.glEnd();
			
			faceMaterial.unsetMaterials(gl);
		}
		
		if(modelTransform != null)
			gl.glPopMatrix();
	}
	
	public void drawOutline(GL2 gl) {
		Material faceMaterial = new DefaultOutlineMaterial();
		
		if(modelTransform != null)
		{
			gl.glPushMatrix();
			modelTransform.transform(gl);
		}
			
		for(int[][] face: faces)
		{
			faceMaterial.setMaterial(gl);
			
			gl.glBegin(GL2.GL_LINE_LOOP);
			
			drawFace(gl, face[0]);
			
			gl.glEnd();
			
			faceMaterial.unsetMaterials(gl);
		}
		
		if(modelTransform != null)
			gl.glPopMatrix();
	}
	
	private void drawFace(GL2 gl, int[] faceVertices)
	{
		int i;
		float[] vertex;

		for(i = 0; i < faceVertices.length; i++)
		{
			vertex = vertices.get(faceVertices[i]);
			
			gl.glVertex3f(vertex[0], vertex[1], vertex[2]);
		}
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
		faces.add(new int[][] { {0, 5, 1}, {0} });
		faces.add(new int[][] { {0, 4, 5}, {0} });
		faces.add(new int[][] { {4, 7, 6}, {0} });
		faces.add(new int[][] { {4, 6, 5}, {0} });
	}
	
	private void initFaceColours()
	{
		Material faceMaterial = new SimpleColourMaterial(ParticleCanvas.DEFUALT_FACE_COLOUR);
		
		materials.add(faceMaterial);
	}
	
}
