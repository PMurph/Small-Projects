package compgeo.point.impl;

import static org.junit.Assert.*;

import org.junit.Test;
import compgeo.point.impl.BasicPoint;
import compgeo.point.excpt.InvalidDimensionException;

public class TestBasicPoint {
	@Test
	public void testDimensionOnlyConstructorValidDimension() throws InvalidDimensionException {
		final int DIMENSION = 4;
		BasicPoint<Integer> testPoint = new BasicPoint<>(DIMENSION);
		
		assertEquals(testPoint.getDimension(), DIMENSION);
	}
	
	@Test
	public void testDimensionCannotBeZero() {
		final int DIMENSION = 0;
		try {
			BasicPoint<Integer> testPoint = new BasicPoint<>(DIMENSION);
			
			fail();
		} catch(InvalidDimensionException ide) {
			assertTrue(ide.getMessage().equals(BasicPoint.INVALID_DIMENSION_MESSAGE));
		}
	}
	
	@Test
	public void testDimensionCannotBeNegative() {
		final int DIMENSION = -42;
		try {
			BasicPoint<Integer> testPoint = new BasicPoint<>(DIMENSION);
			
			fail();
		} catch(InvalidDimensionException ide) {
			assertTrue(ide.getMessage().equals(BasicPoint.INVALID_DIMENSION_MESSAGE));
		}
	}
}
