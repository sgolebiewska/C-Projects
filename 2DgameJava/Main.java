package proj.java;

import proj.java.animals.*;
import proj.java.plants.*;

import java.awt.event.KeyEvent;
import java.util.Random;

public class Main {
	static int worldSize=20;

    public static void main(String[] args) {
     World map = new World(worldSize,worldSize);
     RandNewOrganisms(map);
     map.PrintWorld();
    }

    private static void RandNewOrganisms(World map) {
        Random gen = new Random();
        int amOfOrg = 100;
        for(int i = 0; i < amOfOrg; i++) {
            int x = gen.nextInt(map.GetWidth());
            int y = gen.nextInt(map.GetHeight()); 

            if (map.board[y][x] instanceof Backsplash){
                int org = gen.nextInt(10);
                switch(org){
                    case 0: map.Add(new Antelope(map, new Coords(x,y))); break;
                    case 1: map.Add(new Fox(map, new Coords(x,y)));break;
                    case 2: map.Add(new Grass(map, new Coords(x,y)));break;
                    case 3: map.Add(new Guarana(map, new Coords(x,y)));break;
                    case 4: map.Add(new Sheep(map, new Coords(x,y)));break;
                    case 5: map.Add(new SosnowskyHogweed(map, new Coords(x,y)));break;
                    case 6: map.Add(new Turtle(map, new Coords(x,y)));break;
                    case 7: map.Add(new Wolf(map, new Coords(x,y)));break;
                    case 8: map.Add(new SowThistle(map, new Coords(x,y)));break;
                    case 9: map.Add(new Belladona(map, new Coords(x,y)));break; 
                }
            }
        }
        int x = gen.nextInt(map.GetWidth());
        int y = gen.nextInt(map.GetHeight());
        while(!(map.board[y][x] instanceof Backsplash)){
            x = gen.nextInt(map.GetWidth());
            y = gen.nextInt(map.GetHeight());
        }
        map.Add(new Human(map, new Coords(x,y)));
    }
    
}
