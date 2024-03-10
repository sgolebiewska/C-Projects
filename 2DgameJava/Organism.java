package proj.java;
import javax.swing.*;
import java.awt.*;
import java.util.Random;

public abstract class Organism {
    public int age;
    public int strength;
    public int initiative;
    public World world;
    public Coords position;
    
    public Organism(){}
    
    public Organism(World _world,Coords _coords){
        world = _world;
        position = _coords;
        age=0;
    }
    
    public Organism(World _world, Coords _coords,int _age, int _init, int _strength){ 
        world = _world;
        position = _coords;
        strength = _strength;
        age = _age;
        initiative = _init;
    }
    
    protected Direction RandDir(){
        Direction dir = null;
        Random randGen = new Random();
        int temp = randGen.nextInt(4);
        switch(temp){
            case 0:
                dir = Direction.UP;
                break;
            case 1:
                dir = Direction.DOWN;
                break;
            case 2:
                dir = Direction.LEFT;
                break;
            case 3:
                dir = Direction.RIGHT;
                break;
        }
        return dir;
    }
    
    protected Organism Next(Direction dir, int distance){
        switch (dir) {
            case UP:
                return world.board[position.y - distance][position.x];
            case DOWN:
                return world.board[position.y + distance][position.x];
            case RIGHT:
                return world.board[position.y][position.x + distance];
            case LEFT:
                return world.board[position.y][position.x - distance];

        }
        return this;
    }
    
    void Action(){} 
    
    public void Collision(Organism collider){}
    
    abstract public Color Color(); //organism is abstract
    
    abstract public char GetSign();
    
    abstract public String GetName();
    
}
