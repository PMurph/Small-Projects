package compgeo.point;

import compgeo.point.excpt.DimensionOutOfRangeException;

public interface Point {
	public int getDimension();
	
	public Number getComponent(int dimension) throws DimensionOutOfRangeException;
}
