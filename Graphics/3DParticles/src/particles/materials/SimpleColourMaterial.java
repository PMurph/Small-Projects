package particles.materials;

import javax.media.opengl.GL2;

import particles.ParticleCanvas;

public class SimpleColourMaterial implements Material {

	private float[] matColour;
	
	public SimpleColourMaterial(float[] colour) {
		matColour = new float[4];
		
		assert(colour != null && (colour.length == 3 || colour.length == 4));
		
		if(colour.length == 3 || colour.length == 4)
		{
			System.arraycopy(colour, 0, matColour, 0, colour.length);
			
			if(colour.length == 3)
			{
				matColour[3] = 1;
			}
		}
		else
		{
			System.arraycopy(ParticleCanvas.DEFUALT_FACE_COLOUR, 0, matColour, 0, matColour.length);
		}
	}
	
	public void setMaterial(GL2 gl) {
		gl.glColor4f(matColour[0], matColour[1], matColour[2], matColour[3]);
	}


	public void unsetMaterials(GL2 gl) {
		gl.glColor4f(ParticleCanvas.DEFUALT_FACE_COLOUR[0], ParticleCanvas.DEFUALT_FACE_COLOUR[1], ParticleCanvas.DEFUALT_FACE_COLOUR[2], 
				ParticleCanvas.DEFUALT_FACE_COLOUR[3]);
	}
}
