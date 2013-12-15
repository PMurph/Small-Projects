package particles;

import javax.media.opengl.GL;
import javax.media.opengl.GL2;
import javax.media.opengl.GLAutoDrawable;
import javax.media.opengl.GLCapabilities;
import javax.media.opengl.GLEventListener;
import javax.media.opengl.awt.GLCanvas;
import javax.media.opengl.glu.GLU;


@SuppressWarnings("serial")
public class ParticleCanvas extends GLCanvas implements GLEventListener{
	private final static int INIT_WIDTH = 600, INIT_HEIGHT = 400;
	private final static float[] CLEAR_COLOUR = new float[] { 0.0f, 0.0f, 0.0f, 0.0f };
	private final static GLU glUtils = new GLU();
	
	public final static float[] DEFUALT_FACE_COLOUR = new float[] { 0.5f, 0.5f, 0.5f, 1.0f };
	
	private int width, height;
	private float aspect;
	
	public ParticleCanvas(GLCapabilities capab) {
		super(capab);
		
		initParticleCanvas();
	}

	public void init(GLAutoDrawable drawable) {
		final GL2 gl = drawable.getGL().getGL2();
		
		gl.glClearColor(CLEAR_COLOUR[0], CLEAR_COLOUR[1], CLEAR_COLOUR[2], CLEAR_COLOUR[3]);
		gl.glEnable(GL.GL_CULL_FACE);
	}

	public void dispose(GLAutoDrawable drawable) {
		
	}

	public void display(GLAutoDrawable drawable) {
		final GL2 gl = drawable.getGL().getGL2();

	}

	public void reshape(GLAutoDrawable drawable, int x, int y, int width,
			int height) {
		final GL2 gl = drawable.getGL().getGL2();
	}
	
	private void initParticleCanvas()
	{
		width = INIT_WIDTH;
		height = INIT_HEIGHT;
		
		aspect = width / (float)height;
		
		this.addGLEventListener(this);
		this.setSize(width, height);
	}
}
