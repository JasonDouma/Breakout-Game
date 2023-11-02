#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>
#include <SFML/Audio.hpp>

int main()
{
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(800, 600), "BreakOut");
    //Load Game Font
    sf::Font Space_Invaders;
    Space_Invaders.loadFromFile("space_invaders.ttf");

    // Get Epoche Time For randomized Number
    srand(time(NULL));

    // Loading Sound Files
    sf::SoundBuffer Hit;
    Hit.loadFromFile("HitSound.wav");

    sf::SoundBuffer Destroy;
    Destroy.loadFromFile("Destroy.wav");

    sf::Sound Destroy_sound;
    Destroy_sound.setBuffer(Destroy);

    sf::Sound Hit_Sound;

    Hit_Sound.setBuffer(Hit);

     int Score_num = 0;

    // Creates Text
    sf::Text Score;
    Score.setString("Score: ");
    Score.setFillColor(sf::Color::White);
    Score.setCharacterSize(24);
    Score.setFont(Space_Invaders);
    Score.setPosition(0,0);

    // End Game Text
    sf::Text End_Game_Text;
    End_Game_Text.setFillColor(sf::Color::White);
    End_Game_Text.setCharacterSize(24);
    End_Game_Text.setFont(Space_Invaders);

    float xSpeed = .1;
    float ySpeed = -.1;

    sf::Color colorArray[7]= {sf::Color::Red,
                              sf::Color::Blue,
                              sf::Color::Yellow,
                              sf::Color::Magenta,
                              sf::Color::Green,
                              sf::Color::Cyan,
                              sf::Color::White
                             };

    //Moving Paddle
    sf::RectangleShape Paddle;
    Paddle.setFillColor(sf::Color::White);
    Paddle.setSize(sf::Vector2f(145,15));
    Paddle.setPosition(sf::Vector2f(315,375));

    // Array
    sf::RectangleShape Rect[50];
    int num = 0;

    for (int j = 0; j<5; j++)
    {
        for (int i = 0; i<10; i++)
        {
            Rect[num].setSize(sf::Vector2f(78,18));
            Rect[num].setPosition(sf::Vector2f(i*80, j*20+100));
            Rect[num].setFillColor(colorArray[rand()%7]);
            num++;
        }
    }


    sf::CircleShape Ball(12);
    Ball.setPosition( sf::Vector2f(385, 565));
    Ball.setFillColor(sf::Color::White);


    // Start the game loop
    while (app.isOpen())
    {
        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
            {
                app.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                Paddle.move(-3.5, 0);

            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                Paddle.move(3.5, 0);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                Paddle.move(-3.5, 0);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                Paddle.move(3.5, 0);
            }
        }



        Ball.move(xSpeed, ySpeed);

        if (Ball.getPosition().x <0 || Ball.getPosition().x >775 )
        {
            Hit_Sound.play();
            xSpeed *= -1;
        }

        if (Ball.getPosition().y > 565)
        {

            for (int i = 0; i<50; i++)
            {
                Rect[i].setPosition(0,1000);
            }
            End_Game_Text.setString("Game Over You Got A Score Of: " + std::to_string(Score_num));
            End_Game_Text.setPosition(175,150);
            Score.setPosition(0,1000);
            Paddle.setPosition(0,1000);
            ySpeed = 0;
            xSpeed = 0;

        }

        for (int i=49; i>=0; i--)
        {
            if(Ball.getGlobalBounds().intersects(Rect[i].getGlobalBounds()))
            {
                Hit_Sound.play();
                Destroy_sound.play();
                ySpeed*= -1;
                Rect[i].move(0, -1000);
                Ball.move(0, ySpeed);
                Score_num++;
                Score.setString("Score: " + std::to_string(Score_num));
                int Val = 0;
                Val++;
                if (Val == 50)
                {
                    End_Game_Text.setString("You Win You Got A Perfect Score Of: " + std::to_string(Score_num));
                    Paddle.setPosition(0, 1000);
                    Score.setPosition(0,1000);
                    xSpeed = 0;
                    ySpeed = 0;
                }
                break;
            }
        }

        if (Ball.getGlobalBounds().intersects(Paddle.getGlobalBounds()))
        {
            Hit_Sound.play();
            ySpeed=-.1;
        }

        // Clear screen
        app.clear();

        // Draw Stuff
        for (int i = 0; i<50; i++)
        {
            app.draw(Rect[i]);
        }
        app.draw(Paddle);
        app.draw(Ball);
        app.draw(Score);
        app.draw(End_Game_Text);
        // Update the window
        app.display();
    }

    return EXIT_SUCCESS;
}
