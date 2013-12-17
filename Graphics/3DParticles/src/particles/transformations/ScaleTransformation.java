package particles.transformations;

import javax.media.opengl.GL2;

public class ScaleTransformation implements Transformation{

	private float scaleX, scaleY, scaleZ;
	
	public ScaleTransformation(float x, float y, float z)
	{
		this.scaleX = x;
		this.scaleY = y;
		this.scaleZ = z;
	}
	
	public void transform(GL2 gl) {
		gl.glScalef(scaleX, scaleY, scaleZ);
	}
}
