package particles.transformations;

import javax.media.opengl.GL2;

public class TranslationTransformation implements Transformation{
	
	private float x, y, z;
	
	public TranslationTransformation(float x, float y, float z)
	{
		this.x = x;
		this.y = y;
		this.z = z;
	}

	public void transform(GL2 gl) {		
		gl.glTranslatef(x, y, z);
	}
}
