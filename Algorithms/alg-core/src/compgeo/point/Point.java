package compgeo.point;

public interface Point<E> {
	public int getDimension();
	
	public E getComponent(int dimension);
}
