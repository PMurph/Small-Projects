package particles;

import javax.media.opengl.GL;
import javax.media.opengl.GL2;
import javax.media.opengl.GLAutoDrawable;
import javax.media.opengl.GLCapabilities;
import javax.media.opengl.GLEventListener;
import javax.media.opengl.awt.GLCanvas;
import javax.media.opengl.glu.GLU;

import particles.primitives.Box;
import particles.primitives.Model;


@SuppressWarnings("serial")
public class ParticleCanvas extends GLCanvas implements GLEventListener{
	private final static int INIT_WIDTH = 600, INIT_HEIGHT = 400;
	private final static float[] CLEAR_COLOUR = new float[] { 0.0f, 0.0f, 0.0f, 0.0f };
	private final GLU glUtils = new GLU();
	private final float FIELD_OF_VIEW = 45, DEFAULT_NEAR = 0.5f, DEFAULT_FAR = 5;
	
	public final static float[] DEFUALT_FACE_COLOUR = new float[] { 0.5f, 0.5f, 0.5f, 1.0f };
	public final static float[] DEFAULT_OUTLINE_COLOUR = new float[] { 1.0f, 1.0f, 1.0f, 1.0f };
	public final static float DEFAULT_OUTLINE_WIDTH = 2.0f;
	
	private int width, height;
	private float aspect;
	private WorldBox worldBox;
	
	public ParticleCanvas(GLCapabilities capab) {
		super(capab);
		
		initParticleCanvas();
	}
	
	/* ========================================================
	 * GLEventListener functions
	 * ========================================================
	 */
	
	public void init(GLAutoDrawable drawable) {
		final GL2 gl = drawable.getGL().getGL2();
		
		gl.glClearColor(CLEAR_COLOUR[0], CLEAR_COLOUR[1], CLEAR_COLOUR[2], CLEAR_COLOUR[3]);
		gl.glEnable(GL2.GL_CULL_FACE);
		gl.glCullFace(GL2.GL_BACK);
		gl.glEnable(GL2.GL_DEPTH_TEST);
		gl.glDepthFunc(GL2.GL_LEQUAL);
		
		worldBox = new WorldBox(0.0f, 0.0f, 0.0f, 2, 2, 2);
	}

	public void dispose(GLAutoDrawable drawable) {
		
	}

	public void display(GLAutoDrawable drawable) {
		final GL2 gl = drawable.getGL().getGL2();
		
		gl.glClear(GL2.GL_COLOR_BUFFER_BIT | GL2.GL_DEPTH_BUFFER_BIT);
		
		setupProjection(gl);
		displayScene(gl);
	}

	public void reshape(GLAutoDrawable drawable, int x, int y, int width,
			int height) {
		final GL2 gl = drawable.getGL().getGL2();
		
		this.width = width;
		this.height = height;
		
		aspect = width /(float)(height == 0 ? 1: height);
		
		setupProjection(gl);
	}
	
	/* ========================================================
	 * Helper/Private functions
	 * ========================================================
	 */
	
	private void initParticleCanvas()
	{
		width = INIT_WIDTH;
		height = INIT_HEIGHT;
		
		aspect = width / (float)height;
		
		this.addGLEventListener(this);
		this.setSize(width, height);
	}
	
	private void displayScene(GL2 gl)
	{
		gl.glMatrixMode(GL2.GL_MODELVIEW);
		gl.glLoadIdentity();
		
		glUtils.gluLookAt(0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

		gl.glColor3f(1.0f, 1.0f, 1.0f);
		
		worldBox.drawWorld(gl);
				
		gl.glFlush();
	}
	
	private void setupProjection(GL2 gl)
	{
		gl.glMatrixMode(GL2.GL_PROJECTION);
		gl.glLoadIdentity();
		
		glUtils.gluPerspective(FIELD_OF_VIEW, aspect, DEFAULT_NEAR, DEFAULT_FAR);
	}
}
