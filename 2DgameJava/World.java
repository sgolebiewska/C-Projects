package proj.java;

import proj.java.animals.*;
import proj.java.plants.*;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;
import java.util.LinkedList;
import java.util.List;

import proj.java.animals.Human;
import proj.java.visuals.InfoBar;
import proj.java.visuals.Screen;

public class World  {
    private String text;
    private int cooldown = 0;
    private int width, height;
    public List<Organism> organisms = new LinkedList<>();
    private List<Organism>toAdd = new LinkedList<>();
    private List<Organism>toRem = new LinkedList<>();
    public String notification;
    private boolean humanAlive;
    public JFrame frame;
    public Organism[][] board;
    static int sizeX = 1900;  
    static int sizeY= 1000;
    
    private JTextArea notificationArea;
    private JPanel notificationPanel;
    
    World(int _width, int _height){
        width = _width;
        height = _height;
        board = new Organism[height][width];
        notification="";
        
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                board[i][j] = new Backsplash(); //i use new backsplash because board is of type organism and color is not organism
            }
        }
    }

    public void PrintWorld() {
        frame = new JFrame();
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setLayout(new GridBagLayout()); // Use GridBagLayout for flexible grid

        // Set the size of the frame
        Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
        frame.setSize(screenSize.width , screenSize.height);

        GridBagConstraints constraints = new GridBagConstraints();

        // Create and add the screen
        Screen s = new Screen(frame, this, board, height, width);
        constraints.gridx = 0;
        constraints.gridy = 0;
        constraints.weightx = 0.6;
        constraints.fill = GridBagConstraints.BOTH; // Allow component to resize
        frame.add(s, constraints);

        // Create and add the menu
        InfoBar m = new InfoBar(this, s);
        constraints.gridx = 1;
        constraints.gridy = 0;
        constraints.weightx = 0.2; // Each component takes 25% of the width
        constraints.weighty = 1.0; // Allow vertical resizing
        frame.add(m, constraints);

        // Create the notification panel
        notificationPanel = new JPanel(new BorderLayout());
        JTextArea notificationArea = new JTextArea(10, 50);
        notificationArea.setEditable(false);
        JScrollPane scrollPane = new JScrollPane(notificationArea);
        scrollPane.setPreferredSize(new Dimension(200, 300));
        notificationPanel.add(scrollPane, BorderLayout.CENTER);

        // Add the notification panel to the main frame
        constraints.gridx = 2;
        constraints.gridy = 0;
        constraints.weightx = 0.2; // Each component takes 25% of the width
        frame.add(notificationPanel, constraints);

        frame.setVisible(true);
    }

    public void StartHumanAbility(){
        if(cooldown==0){
            for(Organism it : organisms){
                if(it instanceof Human){
                    ((Human)it).UseAbility();
                    cooldown = 10;
                    notification("SPECIAL ABILITY ACTIVATED!");
                }
            }
        }else {
        	notification("You need to wait a bit to activate special ability!");
        }
    }
    
    public void Add(Organism newO) {
        board[newO.position.y][newO.position.x] = newO;
        int index = organisms.size();
        for (int i = 0; i < organisms.size(); i++) {
            Organism it = organisms.get(i);
            if (newO.initiative > it.initiative) {
                index = i;
                break;
            }
        }
        organisms.add(index, newO);
    }

    public void toAdd(Organism newO) {
        board[newO.position.y][newO.position.x] = newO;
        toAdd.add(newO);
    }

    public void NextTurn(Direction dir) {
        for (Organism it : organisms) {
            if (it.age > 0 && board[it.position.y][it.position.x].GetSign() == it.GetSign()) {
                if (it instanceof Human) {
                    ((Human) it).Action(dir);
                } else {
                    it.Action();
                }
            }
        }
        for (Organism it : toAdd) {
            if (!(it instanceof Backsplash)) {
                Add(it);
            }
        }
        toAdd.clear();
        for (Organism it : organisms) {
            if (it instanceof SosnowskyHogweed) {
                ((SosnowskyHogweed) it).Burn();
            }
        }
        for (Organism it : organisms) {
            if (board[it.position.y][it.position.x] instanceof Backsplash) {
                toRem.add(it);
            }
        }
        organisms.removeAll(toRem);
        toRem.clear();
        for (Organism it : organisms) {
            it.age++;
            if (it instanceof Human && ((Human) it).TurnsLeft() > 0) {
                ((Human) it).Burn();
            }
        }
        if (cooldown > 0) {
            cooldown--;
        }
        frame.invalidate();
        frame.validate();
        frame.repaint();
    }
    
    public int GetHeight(){
    	return height;
    }
    
    public int GetWidth(){ 
    	return width;
    }
    
    public void PrintNotification(){
        System.out.print(notification);
        notification="";
    }
    
    public void notification(String notifications) {
        notification += notifications;
        notification += '\n';
        JTextArea notificationArea = (JTextArea) ((JScrollPane) notificationPanel.getComponent(0)).getViewport().getView();
        notificationArea.setText(notification);
    }
  
    public boolean isHumanAlive(){
    	return humanAlive;
    }
    
    public int AmountOfOrganisms(){ 
    	return organisms.size();
    }
    
    public void Save() {
        JFrame input = createInputFrame();
        JTextField textField = createTextField(input);
        setupSaveActionListener(input, textField);
    }

    public void Load() {
        frame.setVisible(false);
        JFrame input = createInputFrame();
        JTextField textField = createTextField(input);
        setupLoadActionListener(input, textField);
    }

    private JFrame createInputFrame() {
        JFrame input = new JFrame();
        input.setSize(100, 100);
        input.setVisible(true);
        return input;
    }

    private JTextField createTextField(JFrame input) {
        JTextField textField = new JTextField(30);
        input.add(textField);
        return textField;
    }

    private void setupSaveActionListener(JFrame input, JTextField textField) {
        textField.addActionListener(e -> {
            text = textField.getText();
            String saveData = generateSaveData();
            writeSaveDataToFile(saveData);
            input.setVisible(false);
            frame.setVisible(true);
        });
    }

    private String generateSaveData() {
        StringBuilder save = new StringBuilder();
        save.append(width).append(" ").append(height).append(" ").append(organisms.size()).append(" ").append(cooldown).append("\n");
        for (Organism it : organisms) {
            save.append(it.GetSign()).append(" ")
                    .append(it.position.x).append(" ")
                    .append(it.position.y).append(" ")
                    .append(it.age).append(" ")
                    .append(it.strength).append(" ")
                    .append(it.initiative).append(" ");
            if (it instanceof Human) {
                save.append(((Human) it).GetId()).append(" ")
                        .append(((Human) it).TurnsLeft());
            }
            save.append("\n");
        }
        return save.toString();
    }

    private void writeSaveDataToFile(String saveData) {
        try {
            String path = "./src/proj/java/saves/" + text;
            File file = new File(path);
            System.out.println("Write to " + text);
            file.createNewFile();
            BufferedWriter writer = new BufferedWriter(new FileWriter(path));
            writer.write(saveData);
            writer.close();
        } catch (IOException ie) {
            ie.printStackTrace();
        }
    }

    private void setupLoadActionListener(JFrame input, JTextField textField) {
        textField.addActionListener(e -> {
            text = textField.getText();
            System.out.println(text);
            try {
                LoadWorldFromFile(text);
            } catch (IOException ie) {
                ie.printStackTrace();
            }
            input.setVisible(false);
            PrintWorld();
        });
    }

    private void LoadWorldFromFile(String fileName) throws IOException {
        String path = "./src/proj/java/saves/" + fileName;
        File file = new File(path);
        if (file.exists()) {
            notification = "";
            board = null;
            organisms.clear();
            BufferedReader reader = new BufferedReader(new FileReader(path));
            String line = reader.readLine();
            String[] elements = line.split(" ");
            width = Integer.parseInt(elements[0]);//1
            height = Integer.parseInt(elements[1]);//2
            int tempSize = Integer.parseInt(elements[2]);//amount of animals
            cooldown = Integer.parseInt(elements[3]);
            board = new Organism[height][width];
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    board[i][j] = new Backsplash();
                }
            }
            for (int i = 0; i < tempSize; i++) {
                line = reader.readLine();
                elements = line.split(" ");
                switch (elements[0]) {
                    case "@":
                        Add(new Human(this,
                                new Coords(Integer.parseInt(elements[1]), Integer.parseInt(elements[2])),//pos
                                Integer.parseInt(elements[3]),//age
                                Integer.parseInt(elements[4]),//strength
                                Integer.parseInt(elements[5]),//init
                                Integer.parseInt(elements[6]),//id
                                Integer.parseInt(elements[7])));//turns
                        humanAlive = true;
                        break;
                    case "A":
                        Add(new Antelope(this,
                                new Coords(Integer.parseInt(elements[1]), Integer.parseInt(elements[2])),
                                Integer.parseInt(elements[3]),
                                Integer.parseInt(elements[4]),
                                Integer.parseInt(elements[5])));
                        break;
                    case "W":
                        Add(new Wolf(this,
                                new Coords(Integer.parseInt(elements[1]), Integer.parseInt(elements[2])),
                                Integer.parseInt(elements[3]),
                                Integer.parseInt(elements[4]),
                                Integer.parseInt(elements[5])));
                        break;
                    case "F":
                        Add(new Fox(this,
                                new Coords(Integer.parseInt(elements[1]), Integer.parseInt(elements[2])),
                                Integer.parseInt(elements[3]),
                                Integer.parseInt(elements[4]),
                                Integer.parseInt(elements[5])));
                        break;
                    case "S":
                        Add(new Sheep(this,
                                new Coords(Integer.parseInt(elements[1]), Integer.parseInt(elements[2])),
                                Integer.parseInt(elements[3]),
                                Integer.parseInt(elements[4]),
                                Integer.parseInt(elements[5])));
                        break;
                    case "T":
                        Add(new Turtle(this,
                                new Coords(Integer.parseInt(elements[1]), Integer.parseInt(elements[2])),
                                Integer.parseInt(elements[3]),
                                Integer.parseInt(elements[4]),
                                Integer.parseInt(elements[5])));
                        break;
                    case "H":
                        Add(new SosnowskyHogweed(this,
                                new Coords(Integer.parseInt(elements[1]), Integer.parseInt(elements[2])),
                                Integer.parseInt(elements[3]),
                                Integer.parseInt(elements[4]),
                                Integer.parseInt(elements[5])));
                        break;
                    case "G":
                        Add(new Guarana(this,
                                new Coords(Integer.parseInt(elements[1]), Integer.parseInt(elements[2])),
                                Integer.parseInt(elements[3]),
                                Integer.parseInt(elements[4]),
                                Integer.parseInt(elements[5])));
                        break;
                    case "&":
                        Add(new SowThistle(this,
                                new Coords(Integer.parseInt(elements[1]), Integer.parseInt(elements[2])),
                                Integer.parseInt(elements[3]),
                                Integer.parseInt(elements[4]),
                                Integer.parseInt(elements[5])));
                        break;
                    case "B":
                        Add(new Belladona(this,
                                new Coords(Integer.parseInt(elements[1]), Integer.parseInt(elements[2])),
                                Integer.parseInt(elements[3]),
                                Integer.parseInt(elements[4]),
                                Integer.parseInt(elements[5])));
                        break;
                    case "#":
                        Add(new Grass(this,
                                new Coords(Integer.parseInt(elements[1]), Integer.parseInt(elements[2])),
                                Integer.parseInt(elements[3]),
                                Integer.parseInt(elements[4]),
                                Integer.parseInt(elements[5])));
                        break;
                }
            }
            reader.close();
        }
    }

}
