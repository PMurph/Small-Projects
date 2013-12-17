package particles.materials;

import javax.media.opengl.GL2;

import particles.ParticleCanvas;

public class DefaultOutlineMaterial implements Material {
	public void setMaterial(GL2 gl) {
		gl.glLineWidth(ParticleCanvas.DEFAULT_OUTLINE_WIDTH);
		
		gl.glColor4f(ParticleCanvas.DEFAULT_OUTLINE_COLOUR[0], ParticleCanvas.DEFAULT_OUTLINE_COLOUR[1], 
				ParticleCanvas.DEFAULT_OUTLINE_COLOUR[2], ParticleCanvas.DEFAULT_OUTLINE_COLOUR[3]);
	}

	public void unsetMaterials(GL2 gl) {
		gl.glColor4f(ParticleCanvas.DEFUALT_FACE_COLOUR[0], ParticleCanvas.DEFAULT_OUTLINE_COLOUR[1],
				ParticleCanvas.DEFUALT_FACE_COLOUR[2], ParticleCanvas.DEFUALT_FACE_COLOUR[3]);
	}
}
