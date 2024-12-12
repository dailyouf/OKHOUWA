import java.awt.geom.Point2D;
import java.awt.Point;
import java.lang.Math;

public class Carre extends Rectangle {

	private double cote;	
	
	public Carre(Point2D[] points) {
		super(points);
		cote = super.getLgCote(0);
	}
	
	public Carre(Point2D point, double cote) {
		
		this.cote = cote;	
				
		Point2D[] points = new Point[4];
		
		// Point est une classe qui hérite de Point2D
		Point2D point1 = new Point((int) (cote + point.getX()), (int) point.getY());
		Point2D point2 = new Point((int) point.getX(), (int) (cote + point.getY()));
		Point2D point3 = new Point((int) (cote + point.getX()), (int) (cote + point.getY()));

		points[0] = point;
		points[1] = point1;
		points[2] = point2;
		points[3] = point3;
		
		super(points);
	}
	
	@Override
	public double getPerimetre() {
		return 4 * cote;
	}


}
