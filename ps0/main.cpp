// File: main.cpp
// Project: ps0
// Written by: Nolan Allen
// Copyright 2022 Nolan Allen
// Last Update: 11/30/2022

#include <cmath>  // for sin() and cos()
#include <SFML/Graphics.hpp>  // for displaying graphics

class Triple {
 public:
    double x, y, z;  // position or orientation in a 3D world

    Triple() { Triple(0.0, 0.0, 0.0); }
    Triple(double x, double y, double z): x(x), y(y), z(z) {}
};

class Camera {
 private:
    Triple position,  // the camera's position
           direction;  // the camera's direction
    double image_plane_depth;  // determines field of view

 public:
    explicit Camera(double image_plane_depth):
        position(Triple()), direction(Triple()),
        image_plane_depth(image_plane_depth) {}
    // function update
    // used to change the camera's position and direction based on key inputs
    void update(float move_speed, float turn_speed, float x_direction_limit) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            // move forward in the xy plane
            position.x += move_speed * sin(direction.y);
            position.z += move_speed * cos(direction.y);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            // move backward in the xy plane
            position.x -= move_speed * sin(direction.y);
            position.z -= move_speed * cos(direction.y);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            // move right in the xy plane
            position.x += move_speed * cos(direction.y);
            position.z -= move_speed * sin(direction.y);
            // slightly tilt the camera right by an arbitrary amount
            direction.z -= 0.005;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            // move left in the xy plane
            position.x -= move_speed * cos(direction.y);
            position.z += move_speed * sin(direction.y);
            // slightly tilt the camera left by an arbitrary amount
            direction.z += 0.005;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            // turn right
            direction.y += turn_speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            // turn left
            direction.y -= turn_speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            // look up
            direction.x -= turn_speed;
            // limit how far up the camera can turn
            if (direction.x > x_direction_limit)
                direction.x = x_direction_limit;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            // look down
            direction.x += turn_speed;
            // limit how far down the camera can turn
            if (direction.x < 0 - x_direction_limit)
                direction.x = 0 - x_direction_limit;
        }
        // bring the tilt back towards 0 by an arbitrary percentage
        direction.z *= 0.8;
    }
    // getters for camera data
    double x_pos() const { return position.x; }
    double y_pos() const { return position.y; }
    double z_pos() const { return position.z; }
    double x_dir() const { return direction.x; }
    double y_dir() const { return direction.y; }
    double z_dir() const { return direction.z; }
    double get_image_plane_depth() const { return image_plane_depth; }
};

class Object {
 private:
    Triple position,  // the object's position in the world
           rotated_position;  // the object's position relative to the position
                              // and direction of the camera
    // the position and size of the object projected on the image plane
    float projected_x, projected_y, projected_size;
    sf::Sprite sprite;
    // function rotate
    // rotates the object coordinates about the camera
    void rotate(Camera camera) {
        // get the object's offset from the camera
        Triple hold = Triple(position.x - camera.x_pos(),
                             position.y - camera.y_pos(),
                             position.z - camera.z_pos());

        // rotate the object's position in the xz plane about the camera
        // using a rotation matrix
        rotated_position.x =
            hold.z * sin(0 - camera.y_dir()) + hold.x * cos(0 - camera.y_dir());
        rotated_position.z =
            hold.z * cos(0 - camera.y_dir()) - hold.x * sin(0 - camera.y_dir());
        // temporarily hold the new values
        hold.x = rotated_position.x;
        hold.z = rotated_position.z;

        // rotate the object's position in the yz plane about the camera
        // using a rotation matrix
        rotated_position.y =
            hold.z * sin(0 - camera.x_dir()) + hold.y * cos(0 - camera.x_dir());
        rotated_position.z =
            hold.z * cos(0 - camera.x_dir()) - hold.y * sin(0 - camera.x_dir());
        // temporarily hold the new value
        hold.y = rotated_position.y;

        // rotate the object's position in the xy plane about the camera
        // using a rotation matrix
        rotated_position.x =
            hold.y * sin(0 - camera.z_dir()) + hold.x * cos(0 - camera.z_dir());
        rotated_position.y =
            hold.y * cos(0 - camera.z_dir()) - hold.x * sin(0 - camera.z_dir());
    }
    // function project
    // projects the rotated 3D coordinates onto the 2D image plane
    void project(double image_plane_depth) {
        // use 3D projection to get the object's final position on the screen
        projected_x =
            rotated_position.x * image_plane_depth / rotated_position.z;
        projected_y =
            rotated_position.y * image_plane_depth / rotated_position.z;
        projected_size = image_plane_depth / rotated_position.z;
    }

 public:
    Object(double x, double y, double z, sf::Sprite sprite):
        position(Triple(x, y, z)), rotated_position(Triple()),
        projected_x(0.0), projected_y(0.0), projected_size(0.0),
        sprite(sprite) {}
    // draw function
    // calls the rotate and project functions to determine the sprite's position
    // and size on the screen, then draws the sprite at that position and with
    // that size
    void draw(sf::RenderWindow &window, Camera camera) {
        rotate(camera);
        // if the rotated position is in front of the image plane,
        // draw the object
        if (rotated_position.z > camera.get_image_plane_depth()) {
            project(camera.get_image_plane_depth());
            sprite.setPosition(projected_x, projected_y);
            sprite.setScale(projected_size, projected_size);
            double degrees_per_radian = 180 / 3.14159;
            sprite.setRotation(camera.z_dir() * degrees_per_radian);
            window.draw(sprite);
        }
    }
    // getters and setters for object data
    double x() const { return position.x; }
    double y() const { return position.y; }
    double z() const { return position.z; }
    void set_x(double x) { position.x = x; }
    void set_y(double y) { position.y = y; }
    void set_z(double z) { position.z = z; }
    void set_sprite(sf::Sprite new_sprite) { sprite = new_sprite; }
};

int main() {
    // set up the window for the graphics
    sf::RenderWindow window(sf::VideoMode(200, 200), "Doomguy Trio");
    int screen_width = 720,
        frames_per_second = 30;
    window.setFramerateLimit(frames_per_second);
    window.setSize(sf::Vector2u(screen_width, screen_width));

    // obligatory green circle to satisfy project rubric while disregarding
    // artistic integrity
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    // set up the camera object
    Camera camera(300.0);
    float camera_move_speed = 25.0,  // movement speed in units per second
          camera_turn_speed = 0.05,  // turn speed in radians per frame
          // limit for how far you can look up and down in radians
          camera_vertical_direction_limit = 1.0;

    // set up the texture and the sprite to be used in the objects
    sf::Texture texture;
    if (!texture.loadFromFile("./sprite.png"))
        return EXIT_FAILURE;
    sf::Sprite sprite(texture);

    // create three objects in a triangle in fron of the camera
    Object obj1(-250.0, 0.0, 1250.0, sprite);
    Object obj2(250.0, 0.0, 1250.0, sprite);
    Object obj3(0.0, 0.0, 1000.0, sprite);

    // the main loop for the 3D projection engine
    while (window.isOpen()) {
        // poll to see if the window should be closed
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // update the camera position and direction
        camera.update(camera_move_speed, camera_turn_speed,
            camera_vertical_direction_limit);
        // clear the window
        window.clear();
        // draw the objects on the window
        window.draw(shape);
        obj1.draw(window, camera);
        obj2.draw(window, camera);
        obj3.draw(window, camera);
        // display the window
        window.display();
    }

    return 0;
}
