package proj.java;

import java.awt.*;

public class Backsplash extends Organism {
	
    public Backsplash(){}
    
    public Backsplash(World _world, Coords _pos){
        world=_world;
        position=_pos;
    }
    
    @Override
    public Color Color(){
        return new Color(165, 214, 167);
    }

    @Override
    public char GetSign() {
        return 'X';
    }

	@Override
	public String GetName() {
		return "Backsplash";
	}
}
