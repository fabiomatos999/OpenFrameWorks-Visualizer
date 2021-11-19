#include "ofApp.h"
#include <fstream>
//--------------------------------------------------------------
void ofApp::setup()
{

    sound.loadSound("12 Endgame.flac");    //Loads a sound file (in bin/data/)
    sound.setLoop(true);                 // Makes the song loop indefinitely
    sound.setVolume(1);                  // Sets the song volume
    ofSetBackgroundColor(255, 255, 255); // Sets the Background Color
    for (int i = 0; i < 256; i++)
    {
        key_list[i] = 0;
    }
    ofstream of;
    of.open("of.txt");
    of.close();
}

//--------------------------------------------------------------
void ofApp::update()
{
    /* The update method is called muliple times per second
    It's in charge of updating variables and the logic of our app */
    ofSoundUpdate(); // Updates all sound players
    if (t_pressed && current_time > 4000 && (loop_position < key_position + 1))
    {
        ofResetElapsedTimeCounter();
        has4secondselapsed = true;
    }
    current_time = ofGetElapsedTimeMillis();
    if (t_pressed && current_time < 4000 && (loop_position < key_position + 1) && has4secondselapsed == true)
    {
        keyPressed(key_list[loop_position]);
        loop_position++;
        has4secondselapsed = false;
    }
    else if (playing)
    {
        visualizer.updateAmplitudes(); // Updates Amplitudes for visualizer
    }
    if (loop_position >= key_position && t_pressed == true)
    {
        t_pressed = !t_pressed;
        loop_position = 0;
    }
    else
    {
    }
}
//-------------------------------------------------------d-------
void ofApp::draw()
{
    /* The update method is called muliple times per second
    It's in charge of drawing all figures and text on screen */
    if (!playing)
    {
        ofDrawBitmapString("Press 'p' to play some music!", ofGetWidth() / 2 - 50, ofGetHeight() / 2);
    }
    if (t_pressed == false)
    {
        ofDrawBitmapString("", ofGetWidth() - 800, 100);
    }
    if (t_pressed == true)
    {
        ofDrawBitmapString("WE ARE NOW REPLAYING", ofGetWidth() - 800, 100);
    }
    vector<float> amplitudes = visualizer.getAmplitudes();
    if (mode == '1')
    {
        drawMode1(amplitudes);
    }
    else if (mode == '2')
    {
        drawMode2(amplitudes);
    }
    else if (mode == '3')
    {
        drawMode3(amplitudes);
    }
    else if (mode == '4')
    {
        drawMode4(amplitudes);
    }
    else if (mode == '5')
    {
        drawMode5();
    }
}
void ofApp::drawMode1(vector<float> amplitudes)
{
    ofSetBackgroundColor(255, 0, 0); // Sets the Background Color
    ofFill();                        // Drawn Shapes will be filled in with color
    ofSetColor(256);                 // This resets the color of the "brusfh" to white
    ofDrawBitmapString("Rectangle Height Visualizer", 0, 15);
    ofSetColor(colors[0], colors[1], colors[2]);
    ofSetBackgroundColor(0, 128, 255); // Sets the Background Color
    ofDrawBitmapString(songname, 0, 50);
    int xDisp = 0;
    for (int i = 0; i < 65; i++) //loop
    {
        ofDrawRectangle(ofGetWidth() / 64 + xDisp - 16, ofGetHeight() - 100, 50, 3 * amplitudes[i]);
        xDisp += ofGetWidth() / 64;
    }
    ofDrawBitmapString(replaying, ofGetWidth() - 800, 100);
}
void ofApp::drawMode2(vector<float> amplitudes)
{
    ofSetBackgroundColor(255, 128, 0); // Sets the Background Color
    ofSetLineWidth(5);                 // Sets the line width
    ofNoFill();                        // Only the outline of shapes will be drawn
    ofSetColor(256);                   // This resets the color of the "brush" to white
    ofDrawBitmapString("Circle Radius Visualizer", 0, 15);
    ofDrawBitmapString(songname, 0, 50);
    int bands = amplitudes.size();
    for (int i = 0; i < bands; i++)
    {
        ofSetColor((bands - i) * 32 % 256, 18, 144); // Color varies between frequencies
        ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, amplitudes[0] / (i + 1));
    }
    ofDrawBitmapString(replaying, ofGetWidth() - 800, 100);
}

void ofApp::drawMode3(vector<float> amplitudes)
{
    ofDrawBitmapString("Rectangle Width Visualizer", ofGetWidth() - 250, 15);
    // YOUR CODE HERE
    ofSetBackgroundColor(255, 0, 0); // Sets the Background Color
    ofFill();                        // Drawn Shapes will be filled in with color
    ofSetColor(colors[0], colors[1], colors[2]);
    int yDisplacement = 0;
    ofDrawBitmapString(songname, ofGetWidth() - 600, ofGetHeight() - 800);
    for (int i = 0; i < 65; i++)
    {
        ofDrawRectangle(ofGetWidth() / 64 - 15, ofGetHeight() / 64 - 16 + yDisplacement, -1 * 3 * amplitudes[i], ofGetHeight() / 64);
        yDisplacement += ofGetHeight() / 64;
    }
    ofDrawBitmapString(replaying, ofGetWidth() - 800, 100);
}

//---------------------------------------------------------------
void ofApp::drawMode4(vector<float> amplitudes)
{
    ofDrawBitmapString("Custom Visualizer", 0, 15);
    ofSetColor(256); // This resets the color of the "brush" to white
    ofTranslate(ofGetHeight() / 2, ofGetHeight() / 2, 0);
    for (int i = 0; i < 65; i++)
    {
        ofSetColor(ofRandom(255), ofRandom(255), ofRandom(255)); // Sets the Circle Color
    }
    ofSetBackgroundColor(0, 0, 0);
    ofDrawBitmapString(songname, -150, 300);
    ofDrawCircle(0, 0, amplitudes[0] / 5);
    for (int i = 0; i < 65; i++)
    {
        ofRotateDeg(rotatebypi64th + i * (5.625));
        ofDrawRectangle(0, 0, 5, 3 * amplitudes[i]);
    }
    ofDrawBitmapString(replaying, ofGetWidth() - 800, 100);
}
void ofApp::drawMode5()
{
    ofSetColor(256);
    ofTranslate(ofGetHeight() / 2, ofGetWidth() / 2, 0);
    ofSetBackgroundColor(0, 0, 0);
    ofSetColor(255, 255, 255);
    ofDrawBitmapString("You are now recording", 0, 0);
}
//
//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    // This method is called automatically when any key is pressed
    if (r_pressed && key != 'r')
    {
        if (key_position >= 256)
            key_position = 0;
        key_list[key_position] = key;
        key_position++;
        cout << key << endl;
        return;
    }
    switch (key)
    {
    case 'p':
        if (playing)
        {
            sound.stop();
        }
        else
        {
            sound.play();
        }
        playing = !playing;
        break;
    case 'a':
        if (playing)
        {
            sound.setPaused(true);
        }
        if (!playing)
        {
            sound.setPaused(false);
        }
        playing = !playing;
        break;
    case '1':
        mode = '1';
        break;
    case '2':
        mode = '2';
        break;
    case '3':
        mode = '3';
        break;
    case '4':
        mode = '4';
        break;
    case 'd':
        sound.load("clash.wav");
        sound.play();
        songname = "Currently Playing: The Clash - Should I Stay or Should I go";
        playing = true;
        break;
    case 'f':
        sound.load("Goosebumps.wav");
        sound.play();
        songname = "Currently Playing: Travis Scott - Goosebumps";
        playing = true;
        break;
    case 'g':
        sound.load("romeosantos.wav");
        songname = "Currently Playing: Romeo Santos - Propuesta Indecente";
        sound.play();
        playing = true;
        break;
    case 'h':
        sound.load("Darude - Sandstorm.wav");
        songname = "Currently Playing: Darude - Sandstorm";
        sound.play();
        playing = true;
        break;
    case '=':
        if (volume_level >= 1)
        {
            break;
        }
        volume_level = volume_level + 0.1;
        sound.setVolume(volume_level);
        break;
    case '-':
        if (volume_level <= 0)
        {
            break;
        }
        volume_level = volume_level - 0.1;
        sound.setVolume(volume_level);
        break;
    case 'r':
        sound.stop();
        if (!r_pressed)
        {
            r_pressed = true;
            key_position = 0;
            mode = '5';
            for (int i=0; i < 256; i++)
            {
                key_list[i] = 0;
            }
            break;
        }
        if (key == 'r')
        {
            sound.play();
            r_pressed = false;
            ofstream of;
            of.open("of.txt");
            for (int i = 0; i < key_position; i++)
            {
                of << char(key_list[i]) << endl;
            }
            of.close();
            mode = '1';
            break;
        }
    case 't':
        t_pressed_counter++;
        if (!t_pressed)
        {
            t_pressed = true;
        }
        if (t_pressed_counter >= 2)
        {
            t_pressed = false;
            t_pressed_counter =0;
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}
