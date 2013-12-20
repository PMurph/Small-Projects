package particles;

import java.util.ArrayList;

import particles.objects.Particle;

public class CollisionDetector 
{
	private WorldBox worldBox;
	private ArrayList<Particle> particles;
	
	public CollisionDetector(WorldBox wBox)
	{
		this.worldBox = wBox;
		
		particles = new ArrayList<>();
	}
	
	public void registerParticle(Particle newParticle)
	{
		particles.add(newParticle);
	}
	
	public void deregisterParticle(Particle toDeregister)
	{
		boolean removed = false;
		int i;
		
		for(i = 0; i < particles.size() && !removed; i++)
		{
			if(particles.get(i).equals(toDeregister))
			{
				removed = true;
			}
		}
		
		if(removed)
		{
			particles.remove(i);
		}
	}
	
	public WallHit collisionWithTopOrBottom(Particle toCheck)
	{
		WallHit wallHit = WallHit.NONE;
		
		if(toCheck.getPosY() > worldBox.getSizeY() / 2.0f - toCheck.getRadius())
		{
			wallHit = WallHit.TOP;
		}
		else if(toCheck.getPosY() < -(worldBox.getSizeY() / 2.0f - toCheck.getRadius()))
		{
			wallHit = WallHit.BOTTOM;
		}
		
		return wallHit;
	}
	
	public WallHit collisionWithLeftOrRight(Particle toCheck)
	{
		WallHit wallHit = WallHit.NONE;
		
		if(toCheck.getPosX() > worldBox.getSizeX() / 2.0f - toCheck.getRadius())
		{
			wallHit = WallHit.RIGHT;
		}
		else if(toCheck.getPosX() < -(worldBox.getSizeX() / 2.0f - toCheck.getRadius()))
		{
			wallHit = WallHit.LEFT;
		}
		
		return wallHit;
	}
	
	public WallHit collisionWithFrontOrBack(Particle toCheck)
	{
		WallHit wallHit = WallHit.NONE;
		
		if(toCheck.getPosZ() > worldBox.getSizeZ() / 2.0f - toCheck.getRadius())
		{
			wallHit = WallHit.BACK;
		}
		else if(toCheck.getPosZ() > -(worldBox.getSizeZ() / 2.0f - toCheck.getRadius()))
		{
			wallHit = WallHit.FRONT;
		}
		
		return wallHit;
	}
}
