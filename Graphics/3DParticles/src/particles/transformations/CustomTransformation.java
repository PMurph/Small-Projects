package particles.transformations;

import java.util.ArrayList;

import javax.media.opengl.GL2;

public class CustomTransformation implements Transformation {

	private ArrayList<Transformation> transformations;
	
	public CustomTransformation()
	{
		transformations = new ArrayList<Transformation>();
	}
	
	public void addTransformation(Transformation newTransform)
	{
		transformations.add(newTransform);
	}
	
	/* =================================================
	 * Transformation Functions
	 * =================================================
	 */
	
	public void transform(GL2 gl) {
		for(Transformation currTransform: transformations)
		{
			currTransform.transform(gl);
		}
	}
}
