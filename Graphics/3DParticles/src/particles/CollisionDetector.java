package particles;

import java.util.ArrayList;

import particles.objects.Particle;

public class CollisionDetector 
{
	private WorldBox worldBox;
	private ArrayList<Particle> particles;
	private ArrayList<Particle[]> registeredCollisions;
	
	public CollisionDetector(WorldBox wBox)
	{
		this.worldBox = wBox;
		
		particles = new ArrayList<>();
		registeredCollisions = new ArrayList<>();
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
	
	public boolean collisionWithParticle(Particle toCheck)
	{
		boolean collision = false;
		float collisionDistance, currDistance;
		int i;
		Particle part = null;
		
		for(i = 0; i < particles.size() && !collision; i++)
		{
			part = particles.get(i);
			
			if(part != toCheck)
			{
				collisionDistance = part.getRadius() + toCheck.getRadius();
				
				currDistance = distanceBetweenParticles(toCheck, part);
				
				if(collisionDistance >= currDistance)
				{
					collision = true;
				}
			}
		}
		
		return collision;
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
		else if(toCheck.getPosZ() < -(worldBox.getSizeZ() / 2.0f - toCheck.getRadius()))
		{
			wallHit = WallHit.FRONT;
		}
		
		return wallHit;
	}
	
	/* ==================================
	 * Helper Functions
	 * ==================================
	 */
	
	private float distanceBetweenParticles(Particle one, Particle two)
	{
		float distance, deltaX = one.getPosX() - two.getPosX(), deltaY = one.getPosY() - two.getPosY(), deltaZ = one.getPosZ() - two.getPosZ();
		
		distance = (float)Math.sqrt(deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ);
		
		return distance;
	}
}
