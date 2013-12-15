package particles.primitives;

import javax.media.opengl.GL2;

public interface Model {
	public void draw(GL2 gl);
	public void drawOutline(GL2 gl);
}
