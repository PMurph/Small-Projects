package compgeo.point.impl;

import static org.junit.Assert.*;

import org.junit.Test;

import compgeo.point.impl.BasicPoint;
import compgeo.point.excpt.DimensionOutOfRangeException;
import compgeo.point.excpt.InvalidDimensionException;

public class TestBasicPoint {
	@Test
	public void testDimensionOnlyConstructorValidDimension() throws InvalidDimensionException {
		final int DIMENSION = 4;
		BasicPoint testPoint = new BasicPoint(DIMENSION);
		
		assertEquals(testPoint.getDimension(), DIMENSION);
	}
	
	@Test
	public void testDimensionCannotBeZero() {
		final int DIMENSION = 0;
		try {
			BasicPoint testPoint = new BasicPoint(DIMENSION);
			
			fail();
		} catch(InvalidDimensionException ide) {
			assertTrue(ide.getMessage().equals(BasicPoint.INVALID_DIMENSION_MESSAGE));
		}
	}
	
	@Test
	public void testDimensionCannotBeNegative() {
		final int DIMENSION = -42;
		try {
			BasicPoint testPoint = new BasicPoint(DIMENSION);
			
			fail();
		} catch(InvalidDimensionException ide) {
			assertTrue(ide.getMessage().equals(BasicPoint.INVALID_DIMENSION_MESSAGE));
		}
	}
	
	@Test
	public void testGetComponentOfIntegerPointThatHasBeenInitializedWithoutValues() throws InvalidDimensionException, DimensionOutOfRangeException {
		final int DIMENSION = 3;
		final int COMPONENT_DIMENSION = 2;
		BasicPoint testPoint = new BasicPoint(DIMENSION);
		
		assertTrue(testPoint.getComponent(COMPONENT_DIMENSION).intValue() == 0);
	}
	
	@Test
	public void testGetComponentOfDoublePointThatHasBeenInitializedWithoutValues() throws InvalidDimensionException, DimensionOutOfRangeException {
		final int DIMENSION = 4;
		final int COMPONENT_DIMENSION = 1;
		BasicPoint testPoint = new BasicPoint(DIMENSION);
		
		assertTrue(testPoint.getComponent(COMPONENT_DIMENSION).doubleValue() == 0.0);
	}
	
	@Test
	public void testGetComponentOfPointUsingInvalidDimension() throws InvalidDimensionException{
		final int DIMENSION = 1;
		final int COMPONENT_DIMENSION = 1;
		BasicPoint testPoint = new BasicPoint(DIMENSION);
		
		try {
			testPoint.getComponent(COMPONENT_DIMENSION);
			
			fail();
		} catch(DimensionOutOfRangeException doore) {
			assertTrue(doore.getMessage().equals(String.format(BasicPoint.DIMENSION_OUT_OF_RANGE, COMPONENT_DIMENSION, DIMENSION)));
		}
	}
	
	@Test
	public void testSetComponentIntPoint() throws InvalidDimensionException, DimensionOutOfRangeException {
		final int DIMENSION = 3;
		final int COMPONENT_DIMENSION = 1;
		final int TEST_VALUE = 7;
		BasicPoint testPoint = new BasicPoint(DIMENSION);
		
		testPoint.setComponent(COMPONENT_DIMENSION, new Integer(TEST_VALUE));
		assertTrue(testPoint.getComponent(COMPONENT_DIMENSION).intValue() == TEST_VALUE);
	}
}
