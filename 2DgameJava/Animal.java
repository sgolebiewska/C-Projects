package proj.java;

import javax.swing.*;
import java.awt.*;
import java.util.Random;

public class Animal extends Organism{
    public Animal(){}
    
    public Animal(World _world, Coords _pos, int _age, int _strength, int _init){
        super(_world,_pos,_age,_strength,_init);
    }
    
    public Animal(World _world, Coords _pos){
        super(_world, _pos);
    }
    
    @Override
    public void Action() {
        Direction dir = NewDir();
        int newY = position.y;
        int newX = position.x;

        switch (dir) { 
            case UP:
                newY = Math.max(0, position.y - 1);
                break;
            case DOWN:
                newY = Math.min(world.GetHeight() - 1, position.y + 1);
                break;
            case LEFT:
                newX = Math.max(0, position.x - 1);
                break;
            case RIGHT:
                newX = Math.min(world.GetWidth() - 1, position.x + 1);
                break;
        }

        if (newY != position.y || newX != position.x) {
            if (world.board[newY][newX] instanceof Backsplash) {
                Move(dir);
            } else {
                Next(dir, 1).Collision(this);
                if (Next(dir, 1) instanceof Backsplash) { //if wins
                    Move(dir);
                }
            }
        }
    }
    
    protected Direction NewDir() {
        Random randGen = new Random();

        if (position.x == 0) {//checks for specific situations if there isn't any then it gives random direction
            if (position.y == 0)
                return (randGen.nextInt(2) == 0) ? Direction.DOWN : Direction.RIGHT;
            else if (position.y == world.GetHeight() - 1)
                return (randGen.nextInt(2) == 0) ? Direction.UP : Direction.RIGHT;
            else
                return (randGen.nextInt(3) == 0) ? Direction.UP : (randGen.nextInt(2) == 0) ? Direction.DOWN : Direction.RIGHT;
        } else if (position.x == world.GetWidth() - 1) {
            if (position.y == 0)
                return (randGen.nextInt(2) == 0) ? Direction.DOWN : Direction.LEFT;
            else if (position.y == world.GetHeight() - 1)
                return (randGen.nextInt(2) == 0) ? Direction.UP : Direction.LEFT;
            else
                return (randGen.nextInt(3) == 0) ? Direction.UP : (randGen.nextInt(2) == 0) ? Direction.DOWN : Direction.LEFT;
        } else if (position.y == 0)
            return (randGen.nextInt(3) == 0) ? Direction.RIGHT : (randGen.nextInt(2) == 0) ? Direction.DOWN : Direction.LEFT;
        else if (position.y == world.GetHeight() - 1)
            return (randGen.nextInt(3) == 0) ? Direction.UP : (randGen.nextInt(2) == 0) ? Direction.RIGHT : Direction.LEFT;
        else
            return RandDir();
    }
    
    protected void Move(Direction dir) {
        int newY = position.y;
        int newX = position.x;

        switch (dir) {
            case UP:
                newY = Math.max(0, position.y - 1);
                break;
            case DOWN:
                newY = Math.min(world.GetHeight() - 1, position.y + 1);
                break;
            case LEFT:
                newX = Math.max(0, position.x - 1);
                break;
            case RIGHT:
                newX = Math.min(world.GetWidth() - 1, position.x + 1);
                break;
        }

        if (newY != position.y || newX != position.x) {
            world.board[newY][newX] = world.board[position.y][position.x];
            world.board[position.y][position.x] = new Backsplash();
            position.y = newY;
            position.x = newX;
        }
    }
 
    @Override
    public char GetSign(){
        return 'A';
    }
    
    @Override
    public Color Color(){
       return Color.RED;
    }
    
    public void Collision(Organism collider) { //default for wolf, sheep and fox
        if(collider.GetSign() == this.GetSign()){
        	world.notification(collider.GetName() +"("+ collider.position.x+ ", "+ collider.position.y + ") made a baby with " + this.GetName()+"("+ this.position.x+ ", "+ this.position.y + ")");
            MakeBaby();
        }
        else if (collider.strength > this.strength){
        	Random randGen = new Random();
        	int temp = randGen.nextInt(2);
        	if(temp==1)world.notification("What a spectacular kill!");
            world.notification(collider.GetName() +"("+ collider.position.x+ ", "+ collider.position.y + ") kills " + this.GetName()+"("+ this.position.x+ ", "+ this.position.y + ")");
            world.board[position.y][position.x]=new Backsplash();
        }
        else{
        	Random randGen = new Random();
        	int temp = randGen.nextInt(2);
        	if(temp==1)world.notification("That was something amazing!");
            world.notification(this.GetName() +"( "+ this.position.x+ ", "+ this.position.y + ") kills " + collider.GetName()+"("+ collider.position.x+ ", "+ collider.position.y + ")");
            world.board[collider.position.y][collider.position.x]=new Backsplash();
        }
    }
    
    protected void MakeBaby(){}
    
	@Override
	public String GetName() {
		return "Animal";
	}

}
