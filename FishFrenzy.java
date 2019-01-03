package Controller;

import java.io.InputStream;
import java.net.URL;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Random;

import javax.print.DocFlavor.STRING;

import Model.*;

import View.Instructions;
import View.FinalScene;

import javafx.animation.AnimationTimer;
import javafx.application.Application;
import javafx.event.EventHandler;
import javafx.geometry.Pos;
import javafx.scene.*;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.scene.layout.*;
import javafx.scene.media.AudioClip;
import javafx.scene.media.Media;
import javafx.scene.media.MediaPlayer;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.FontWeight;
import javafx.stage.Stage;


public class FishFrenzy extends Application{
	private Scene scene;
	private Pane gamePane;
	private MainFish player;
	private ArrayList<Item> fishList;
	private AnimationTimer timer;
//	private OpeningScene openScene;
	private Pane pane;
	private VBox table;
	private VBox box;
	private Stage stage;
	private Scene open;
	private Live heart;
	private Hook hook;
	private FinalScene lost, won;

	private Button menu, exit;
	private MediaPlayer PlayIt;
	private MagicChest treasure;
	private long timeStart;
	private Scene inst, ender;
	private Button startHard, startEasy, instructions;
	private static final String url = "../Audio/UnderTheSea.mp3";
	@Override
	public void start(Stage stage) throws Exception {
		
		this.stage = stage;
		gamePane = new Pane();
	
		fishList = new ArrayList<>();
		BackgroundImage myBI= new BackgroundImage(new Image("/View/Ocean.png",1400,700,false,true),
		        BackgroundRepeat.NO_REPEAT, BackgroundRepeat.NO_REPEAT, BackgroundPosition.DEFAULT,
		          BackgroundSize.DEFAULT);
		gamePane.setBackground(new Background(myBI));
		table = new VBox();
		menu = new Button("Play Again");//set up for intro
		exit = new Button("Exit Game");
		menu.setStyle("-fx-background-color: " + "darkblue");
		menu.setTextFill(Color.WHITE);
		exit.setStyle("-fx-background-color: " + "darkblue");
		exit.setTextFill(Color.WHITE);
		Button goBack = new Button("Return to Menu");
		goBack.setStyle("-fx-background-color: " + "powderblue");
		goBack.setTextFill(Color.DARKBLUE);
		goBack.setOnAction(e ->  {
			stage.setScene(open);
		});
		Instructions instruct = new Instructions(stage, goBack);
		inst = instruct.getScene();
		menu.setOnAction(e-> {
			stage.close();
			try {
				start(stage);
			} catch (Exception e1) {
				
				e1.printStackTrace();
			}
	
			stage.show();
		});
		exit.setOnAction( e-> {
			stage.close();
		});
		
		lost = new FinalScene(menu, exit, "So sorry, you lost!");
		won = new FinalScene(menu, exit, "Congratulations! You're full on treasure!");
		setUpStart();
		stage.show();

	}
	
	private void setUpStart() { //setting up the start screen
		
		Label label = new Label("Fish Frenzy");
		label.setTextFill(Color.DARKBLUE);
		
		
		label.setFont(Font.font("Verdana",FontWeight.BOLD, 38.0));
		
		startEasy = new Button("Easy Mode");
		startEasy.setStyle("-fx-background-color: " + "darkblue");
		startEasy.setTextFill(Color.WHITE);
		startEasy.setOnAction(e ->{
			startGame("normal");
		});
		startHard = new Button("Chaos Mode");
		startHard.setStyle("-fx-background-color: " + "darkblue");
		startHard.setTextFill(Color.WHITE);
		startHard.setOnAction(e ->{
			startGame("chaos");
		});
		instructions = new Button("Instructions");
		instructions.setStyle("-fx-background-color: " + "darkblue");
		instructions.setTextFill(Color.WHITE);
		instructions.setOnAction(e -> {
			stage.setScene(inst);
			
		});
		BackgroundImage BI= new BackgroundImage(new Image("/View/opening.jpg",700, 500,false,true),
		        BackgroundRepeat.NO_REPEAT, BackgroundRepeat.NO_REPEAT, BackgroundPosition.DEFAULT,
		          BackgroundSize.DEFAULT);
		
		table.getChildren().addAll(label, instructions, startEasy, startHard);
		table.setSpacing(20);

		table.setAlignment(Pos.CENTER);
		table.setBackground(new Background(BI));
		
	
		
		open = new Scene(table, 700, 500);
		stage.setScene(open);
		
		
	}
	private void startGame(String level) {
		Scene scene = new Scene(gamePane, 1200, 700);
		Media media = new Media(getClass().getResource(url).toString());
		PlayIt = new MediaPlayer(media);
		PlayIt.play();
		
		doAnimation();
		timeStart = System.currentTimeMillis();
		scene.setOnKeyPressed(new EventHandler<KeyEvent>() {
			@Override
			public void handle(KeyEvent event) {
				
				KeyCode code = event.getCode();
				
				if(code == KeyCode.W) {//fish up
					player.moveUp();
			
				}
				if(code == KeyCode.S) {//fish down
					player.moveDown();
					
				}
				if(code == KeyCode.D) {//fish right
					player.moveRight();
					player.setScaleX(-1.0);

				}
				if(code == KeyCode.A) {//right left
					player.moveLeft();
					player.setScaleX(1.0);
				}
			}
		});
		
		setUpElements(level);
		
		
		stage.setScene(scene);
		timer.start();
		
	}

	private void setUpElements(String level) {
		if(level.equals("chaos")){
			player = new MainFish(600, 10, 30, 30);
			treasure = new MagicChest(990, 490, 210, 210);
			chaosFish();
		}
		else {
			player = new MainFish(600, 10, 36, 36);
			treasure = new MagicChest(1050, 550, 150, 150);
			addFish();
		}
		
		Random random = new Random();
		heart = new Live(random.nextInt(800) + 20, random.nextInt(400) + 20, 30, 30);
		hook = new Hook(random.nextInt(800) + 20, random.nextInt(400), 40, 40);
		gamePane.getChildren().addAll(player,  treasure, heart, hook);
		
	}
	public static void main(String[] args) {
		launch(args);
	}
	public void chaosFish() { //adding fish for chaos mode
		for(int i = 0; i < 52; i++) {
			Random random = new Random();
			double x = random.nextInt(1001);
			double y = random.nextInt(600) + 40;
			double width = random.nextInt(85) + 5;
			double height = random.nextInt(85) + 5;
			int dir = random.nextInt(2);
			Fish tmp = new Fish(x, y, width, height, dir);
			
			fishList.add(tmp);
			
			gamePane.getChildren().add(tmp);
		}
		for(int i = 0; i < 5; i++) {
			Random random = new Random();
			double x = random.nextInt(901);
			double y = random.nextInt(701);
			double width = random.nextInt(30) + 10;
			double height = random.nextInt(30) + 10;
			
			PufferFish tmp = new PufferFish(x, y, width, height);
			fishList.add(tmp);
			gamePane.getChildren().add(tmp);
		}
		
	}
	public void addFish() {//adding fish for easy mode
		for(int i = 0; i < 35; i++) {
			Random random = new Random();
			double x = random.nextInt(1001);
			double y = random.nextInt(600) + 40;
			double width = random.nextInt(55) + 5;
			double height = random.nextInt(55) + 5;
			int dir = random.nextInt(2);
			Fish tmp = new Fish(x, y, width, height, dir);
			
			fishList.add(tmp);
			
			gamePane.getChildren().add(tmp);
		}
		for(int i = 0; i < 5; i++) {
			Random random = new Random();
			double x = random.nextInt(901);
			double y = random.nextInt(701);
			double width = random.nextInt(30) + 10;
			double height = random.nextInt(30) + 10;
			
			PufferFish tmp = new PufferFish(x, y, width, height);
			fishList.add(tmp);
			gamePane.getChildren().add(tmp);
		}
		
	}
	public void moveFish(Fish f) {
		
		f.setX(f.getX() + f.getSpeed());
	}
	public void movePufferFish(PufferFish f) {
		
		f.setX(f.getX() + 1);
	}
	public void setUpEnd() { //set up end view
		VBox box = new VBox();
		BackgroundImage myBI= new BackgroundImage(new Image("/View/opening.jpg",700,700,false,true),
		        BackgroundRepeat.NO_REPEAT, BackgroundRepeat.NO_REPEAT, BackgroundPosition.DEFAULT,
		          BackgroundSize.DEFAULT);
		box.setBackground(new Background(myBI));
		Label sad = new Label("Your fish didn't make it! Better luck next time!");
		sad.setFont(Font.font("Verdana",FontWeight.BOLD, 22.0));
		sad.setTextFill(Color.DARKBLUE);
		box.setSpacing(20);
		box.getChildren().addAll(sad, menu, exit);

		box.setAlignment(Pos.CENTER);
		ender = new Scene(box, 700, 600);
		
	}
	
	private void doAnimation() { //animation
		timer = new AnimationTimer(){
			boolean hasLife = false;
			
			
			@Override
			public void handle(long now) {
				Iterator itr = fishList.iterator();
		
				if(player.getBoundsInParent().contains(treasure.getBoundsInParent())) {
					
					gamePane.getChildren().remove(treasure);
					timer.stop();
					PlayIt.stop();
					long timeEnd = System.currentTimeMillis() - timeStart;
					won.setTime(timeEnd);
					stage.setScene(won.getScene());
				}
				if(player.getBoundsInParent().contains(heart.getBoundsInParent())) {
					gamePane.getChildren().remove(heart);
					hasLife = true;
				}
				if(hook.getBoundsInParent().intersects(player.getBoundsInParent())) {
					gamePane.getChildren().remove(hook);
					timer.stop();
					PlayIt.stop();
					setUpEnd();
					stage.setScene(ender);
				}
				
				while(itr.hasNext()) {
					Item fish = (Item) itr.next();
					if(player.getBoundsInParent().contains(fish.getBoundsInParent())) {
							if(fish.getType().equals("PufferFish")){
								if(!hasLife) {
									gamePane.getChildren().remove(player);
									timer.stop();
									PlayIt.stop();
									setUpEnd();
									stage.setScene(ender);
								}
								else hasLife = false;
							}
							player.setSpeed();
							itr.remove();
							gamePane.getChildren().remove(fish);
							player.grow();
					
					}
					else if(fish.getBoundsInParent().contains(player.getBoundsInParent())) {//if fish gets swallowed
						if(!hasLife) {
							gamePane.getChildren().remove(player);
							timer.stop();
							PlayIt.stop();
							setUpEnd();
							stage.setScene(ender);
						}
						else hasLife = false;
					}
					if(fish.getX() > 1200) {
						fish.setX(1.0);
						fish.setY(fish.getY());
						if(fish.getType().equals("PufferFish")) {
							movePufferFish((PufferFish)fish);
						}
						else {
							moveFish((Fish)fish);
						}
						
					}
					if(fish.getX() < 0) {
						fish.setX(1190.0);
						fish.setY(fish.getY());
						if(fish.getType().equals("PufferFish")) {
							movePufferFish((PufferFish)fish);
						}
						else {
							moveFish((Fish)fish);
						}
						
					}
					if(fish.getType().equals("PufferFish")) {
						movePufferFish((PufferFish)fish);
					}
					else {
						moveFish((Fish)fish);
					}
					
				}
		
			}
			
		};
	}
	

}
