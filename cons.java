import java.util.*;

public class Cons{
	
	int age;
	String name;
	Cons(){
		this.name = "himesh";
		this.age = 21;
		System.out.println(this.age+" "+this.name);
	}
	Cons(int age,String name){
		this.name = name;
		this.age = age;
		System.out.println(this.age+" "+this.name);
	}
	Cons(Cons s){
		System.out.println(s.age);	
	}

	public static void main(String args[]){
		Cons st = new Cons(14,"himesh");
		Cons st1 = new Cons();
		// copy constructor
		Cons s1 = new Cons(st1);
		Cons s = new Cons(st);
	}
}