import java.util.ArrayList;
import java.util.List;
import java.util.Iterator;

public class TestAFList {
  public static void main(String[] args) {
    List<String> data = List.of("a", "b", "c", "d", "e", "f", "g", "h");
    ArrayFIFOList<String> l = new ArrayFIFOList<String>(data);
    System.out.println("l=" + l);
    l.add(3, "z");
    System.out.println("l + z en pos 3=" + l);
    System.out.println("l.rank(\"z\")=" + l.rank("z"));
    System.out.println("l.get()=" + l.get());
    System.out.println("l.remove()=" + l.remove());
    System.out.println("l=" + l);
    System.out.println("l.rank(\"d\")=" + l.rank("d"));
    System.out.println("l.rank(\"g\")=" + l.rank("g"));
    System.out.println("l.remove(\"e\")=" + l.remove("e"));
    System.out.println("l=" + l);
    System.out.println("l.rank(\"e\")=" + l.rank("e"));
  }

}
