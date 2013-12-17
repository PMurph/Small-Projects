package particles;

import javax.media.opengl.GL2;

import particles.primitives.Box;
import particles.transformations.CustomTransformation;
import particles.transformations.ScaleTransformation;
import particles.transformations.Transformation;
import particles.transformations.TranslationTransformation;

public class WorldBox {
	private float positionX, positionY, positionZ;
	private float sizeX, sizeY, sizeZ;
	private Box worldBox;
	private Transformation modelTransform;
	
	public WorldBox(float x, float y, float z, float sizeX, float sizeY, float sizeZ)
	{
		this.positionX = x;
		this.positionY = y;
		this.positionZ = z;
		
		this.sizeX = sizeX;
		this.sizeY = sizeY;
		this.sizeZ = sizeZ;
		
		worldBox = new Box();
		
		modelTransform = initModelTransformation();
	}
	
	public void drawWorld(GL2 gl)
	{
		gl.glPushMatrix();
		
		modelTransform.transform(gl);
		
		gl.glCullFace(GL2.GL_FRONT);
		
		worldBox.draw(gl);
		
		gl.glCullFace(GL2.GL_BACK);
		
		worldBox.drawOutline(gl);
		
		gl.glPopMatrix();
	}
	
	private Transformation initModelTransformation() {
		CustomTransformation transform = new CustomTransformation();
		
		transform.addTransformation(new TranslationTransformation(this.positionX, this.positionY, this.positionZ));
		transform.addTransformation(new ScaleTransformation(sizeX, sizeY, sizeZ));
		transform.addTransformation(new TranslationTransformation(-0.5f, -0.5f, 0.5f));
		
		return transform;
	}
}
