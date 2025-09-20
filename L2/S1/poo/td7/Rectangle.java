import java.awt.geom.Point2D;
import java.awt.Point;
import java.lang.Math;

public class Rectangle extends Quadrilatere{
	
	private double longueur, largeur;
	
	
	public Rectangle(Point2D[] points) {
		super(points);
		longueur = super.getLgCote(0);
		largeur = super.getLgCote(1);
	}
	
	public Rectangle(Point2D point, double largeur, double longueur) {
	
		this.largeur = largeur;
		this.longueur = longueur;
		
		Point2D[] points = new Point[4];
		
		// Point est une classe qui hérite de Point2D
		Point2D point1 = new Point((int) (longueur + point.getX()), (int) point.getY());
		Point2D point2 = new Point((int) point.getX(), (int) (largeur + point.getY()));
		Point2D point3 = new Point((int) (longueur + point.getX()), (int) (largeur + point.getY()));
		
		points[0] = point;
		points[1] = point1;
		points[2] = point2;
		points[3] = point3;
		
		super(points);
	}
	
	@Override
	public double getPerimetre() {
		return 2 * (longueur + largeur);
	}

}
