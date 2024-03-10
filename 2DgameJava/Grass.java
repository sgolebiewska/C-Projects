package proj.java;

import java.awt.*;
import java.util.LinkedList;
import java.util.Random;
import java.util.List;
public class Grass extends Organism {
    public Grass(){}
    
    public Grass(World _world, Coords _pos, int _age, int _strength, int _init){
        super(_world,_pos,_age,_strength,_init);
    }
    
    public Grass(World _world, Coords _pos){
        super(_world, _pos);
        strength = 0;
        initiative = 0;
    }
    
    @Override
    public char GetSign(){
        return '#';
    } 

    @Override
    public Color Color() {
        return new Color(156, 204, 101);
    }
    
    @Override
    public void Action() {
        Random gen = new Random();
        int temp = gen.nextInt(10);

        if (temp == 0) {
            List<Direction> chances = new LinkedList<>();

            if (position.x == 0) {
                if (position.y == 0) {
                    addValidDirections(chances, Direction.DOWN, Direction.RIGHT);
                } else if (position.y == world.GetHeight() - 1) {
                    addValidDirections(chances, Direction.UP, Direction.RIGHT);
                } else {
                    addValidDirections(chances, Direction.UP, Direction.DOWN, Direction.RIGHT);
                }
            } else if (position.x == world.GetWidth() - 1) {
                if (position.y == 0) {
                    addValidDirections(chances, Direction.DOWN, Direction.LEFT);
                } else if (position.y == world.GetHeight() - 1) {
                    addValidDirections(chances, Direction.UP, Direction.LEFT);
                } else {
                    addValidDirections(chances, Direction.UP, Direction.DOWN, Direction.LEFT);
                }
            } else if (position.y == 0) {
                addValidDirections(chances, Direction.DOWN, Direction.LEFT, Direction.RIGHT);
            } else if (position.y == world.GetHeight() - 1) {
                addValidDirections(chances, Direction.UP, Direction.LEFT, Direction.RIGHT);
            } else {
                addValidDirections(chances, Direction.UP, Direction.DOWN, Direction.LEFT, Direction.RIGHT);
            }

            MakePlantBaby(chances);
        }
    }

    protected void addValidDirections(List<Direction> chances, Direction... directions) {
        for (Direction direction : directions) {
            int nextX = position.x;
            int nextY = position.y;

            switch (direction) {
                case UP:
                    nextY--;
                    break;
                case DOWN:
                    nextY++;
                    break;
                case LEFT:
                    nextX--;
                    break;
                case RIGHT:
                    nextX++;
                    break;
            }

            if (world.board[nextY][nextX] instanceof Backsplash) {
                chances.add(direction);
            }
        }
    }

    protected void MakePlantBaby(List<Direction> chances) {
        Random gen = new Random();

        if (chances.size() == 0) {
            return;
        } else {
            int temp = gen.nextInt(chances.size());
            Direction selectedDirection = chances.get(temp);

            int nextX = position.x;
            int nextY = position.y;

            switch (selectedDirection) {
                case UP:
                    nextY--;
                    break;
                case DOWN:
                    nextY++;
                    break;
                case LEFT:
                    nextX--;
                    break;
                case RIGHT:
                    nextX++;
                    break;
            }

            world.toAdd(new Grass(world, new Coords(nextX, nextY)));
            world.notification(this.GetName() +"("+this.position.x+", "+ this.position.y+") is spreading!!");
        }
    }

    @Override
    public void Collision(Organism collider){
        world.notification(collider.GetName() +"("+collider.position.x+", "+ collider.position.y+") eats "+ this.GetName()+"("+this.position.x+", "+ this.position.y+")");
        world.board[position.y][position.x] = new Backsplash();
    }
    
	@Override
	public String GetName() {
		return "Grass";
	}
}
