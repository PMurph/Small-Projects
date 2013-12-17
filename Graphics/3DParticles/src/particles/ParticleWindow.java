package particles;

import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import javax.media.opengl.GLCapabilities;
import javax.media.opengl.GLProfile;
import javax.swing.JFrame;

@SuppressWarnings("serial")
public class ParticleWindow extends JFrame implements MouseMotionListener{
	private final static String WINDOW_TITLE = "3D Particles Window";
	
	private ParticleCanvas partCanvas;
	
	public ParticleWindow()
	{
		super(WINDOW_TITLE);
		
		initWindow();
	}
	
	public void mouseDragged(MouseEvent e) {
		
	}

	public void mouseMoved(MouseEvent e) {
		int winX = e.getX(), winY = e.getY();
		int winWidth = this.getWidth(), winHeight = this.getHeight();
		float deltaX, deltaY;
		
		deltaX = getDelta(winWidth, winX);
		deltaY = getDelta(winHeight, winY);
		
		partCanvas.changeDelta(deltaX, deltaY);
	}
	
	private float getDelta(int winDimension, int winPos)
	{
		float delta = 0.0f;
		int click, max;
		
		if(winPos > (3*winDimension / 4))
		{
			max = winPos - (3*winDimension / 4);
			click = winPos - (3*winDimension / 4);
			
			delta = click / (float)max;
		}
		else if(winPos < (winDimension / 4))
		{
			max = (winDimension / 4);
			click = winPos - (winDimension / 4);
			
			delta = click / (float)max;
		}
		
		return delta;
	}

	private void initWindow()
	{
		final GLProfile profile = GLProfile.get(GLProfile.GL2);
		final GLCapabilities capab = new GLCapabilities(profile);
		
		partCanvas = new ParticleCanvas(capab);
		
		this.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent e)
			{
				System.exit(0);
			}
		});
		
		this.addMouseMotionListener(this);
		
		this.getContentPane().add(partCanvas);
		this.pack();
		this.setVisible(true);
	}
}
