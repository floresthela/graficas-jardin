//
//  main.cpp
//  jardin-opengl
//
//  Created by Flor Esthela on 11/05/20.
//  Copyright © 2020 Flor Esthela. All rights reserved.
//

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

void keyCallback( GLFWwindow *window, int key, int scancode, int action, int mods );

void DrawTop(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength);

void Pata1(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength);
void Pata2(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength);
void Pata3(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength);
void Pata4(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength);

GLfloat rotationX = 0.0f;
GLfloat rotationY = 0.0f;
GLfloat translationX = 0.0f;
GLfloat translationY = 0.0f;
GLfloat escalar = 1.0f;

int main(void) {
    GLFWwindow *window;
    
    // Inicializar la librería
    if (!glfwInit()){
        return -1;
    }
    
    // Crear la ventana
    window = glfwCreateWindow( SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", NULL, NULL );
    
    // Declarar que se recibirán comando del teclado
    glfwSetKeyCallback( window, keyCallback );
    glfwSetInputMode( window, GLFW_STICKY_KEYS, 1 );
    
    
    
    int screenWidth, screenHeight;
    glfwGetFramebufferSize( window, &screenWidth, &screenHeight );
    
    
    if ( !window )
    {
        glfwTerminate( );
        return -1;
    }
    
    // Se crea el contexto de la ventana
    glfwMakeContextCurrent( window );
    
    glViewport( 0.0f, 0.0f, screenWidth, screenHeight ); // Específica en que parte de la ventana se dibujaran los elementos
    glMatrixMode( GL_PROJECTION ); // Se crea la matriz de proyección
    glLoadIdentity( ); // Se crea de la matriz identidad
    glOrtho( 0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1000 ); // Establecer el sistema de coordenadas
    glMatrixMode( GL_MODELVIEW ); // Matriz de transformación
    
    
    // Se establece el sistema de coordenadas dentro de la ventana
    GLfloat halfScreenWidth = SCREEN_WIDTH / 2;
    GLfloat halfScreenHeight = SCREEN_HEIGHT / 2;
    
    
    // Loop en donde se estará dibujando la ventana
    while ( !glfwWindowShouldClose( window ) )
    {
        glClear( GL_COLOR_BUFFER_BIT );
        glClear(GL_DEPTH_BUFFER_BIT);
        
        // Render (Se crea el cubo y se generan los cambios en los vectores de transformación
        
        glPushMatrix( );
        glTranslatef( halfScreenWidth, halfScreenHeight, -500 ); // Coloca el cubo al centro de la pantalla
        glTranslated(translationX, translationY,0); // Mueve el cubo con las variables de las teclas (Vector de Traslación
        
        //Aquí se crearía el vector de escalado
        glScalef(escalar, escalar, escalar);
        
        glRotatef( rotationX, 1, 0, 0 ); // Rotar el cubo en X
        glRotatef( rotationY, 0, 1, 0 ); // Rotar el cubo en Y
        glTranslatef( -halfScreenWidth, -halfScreenHeight, 500 );
        
        DrawTop(halfScreenWidth, halfScreenHeight, -500, 200);
        Pata1(halfScreenWidth, halfScreenHeight, -500, 200);
        Pata2(halfScreenWidth, halfScreenHeight, -500, 200);
        Pata3(halfScreenWidth, halfScreenHeight, -500, 200);
        Pata4(halfScreenWidth, halfScreenHeight, -500, 200);
        // dibuja las demás figuras
        
        glPopMatrix();
        glfwSwapBuffers( window );
        glfwPollEvents( );
    }
    
    glfwTerminate( );
    
    return 0;
}


// LLamar mandar las teclas
void keyCallback( GLFWwindow *window, int key, int scancode, int action, int mods )
{
    const GLfloat rotationSpeed = 10;
    
    // Switch en donde se determinan los movimientos del cubo en base a las teclas
    if ( action == GLFW_PRESS || action == GLFW_REPEAT )
    {
        switch ( key )
        {
            case GLFW_KEY_UP:
                rotationX -= rotationSpeed;
                break;
            case GLFW_KEY_DOWN:
                rotationX += rotationSpeed;
                break;
            case GLFW_KEY_RIGHT:
                rotationY += rotationSpeed;
                break;
            case GLFW_KEY_LEFT:
                rotationY -= rotationSpeed;
                break;
            case GLFW_KEY_A:
                translationX -= 10;
                break;
            case GLFW_KEY_S:
                translationX += 10;
                break;
            case GLFW_KEY_W:
                translationY += 10;
                break;
            case GLFW_KEY_X:
                translationY -=10;
                break;
            case GLFW_KEY_1: // escalar disminuye el tamaño con la tecla del número 1
                escalar -= 0.1;
                break;
            case GLFW_KEY_2: // escalar aumenta el tamaño con la tecla del número 2
                escalar += 0.1;
                break;
        }
        
        
    }
}


void DrawTop( GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength )
{
    GLfloat halfSideLength = edgeLength * 0.5f;
    
    GLfloat vertices[] =
    {
        
        // Cara frontal
        centerPosX - halfSideLength - 100, centerPosY + halfSideLength, centerPosZ + halfSideLength, // P1 Arriba Izquierda
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // P2 Arriba Derecha
        centerPosX + halfSideLength, centerPosY - halfSideLength + 180, centerPosZ + halfSideLength, // P4 Abajo Derecha
        centerPosX - halfSideLength - 100, centerPosY - halfSideLength + 180, centerPosZ + halfSideLength, // P3 Abajo Izquierda
        
        // Cara Trasera
        centerPosX - halfSideLength - 100, centerPosY + halfSideLength, centerPosZ - halfSideLength, // P7 Arriba Izquierda
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // P8 Arriba Derecha
        centerPosX + halfSideLength, centerPosY - halfSideLength + 180, centerPosZ - halfSideLength, // P6 Abajo Derecha
        centerPosX - halfSideLength - 100, centerPosY - halfSideLength + 180, centerPosZ - halfSideLength, // P5 Abajo Izquierda
        
        // Cara Izquierda
        centerPosX - halfSideLength - 100, centerPosY + halfSideLength, centerPosZ + halfSideLength, // P7 Arriba Izquierda
        centerPosX - halfSideLength - 100, centerPosY + halfSideLength, centerPosZ - halfSideLength, // P1 Arriba Dereccha
        centerPosX - halfSideLength - 100, centerPosY - halfSideLength + 180, centerPosZ - halfSideLength, // P3 Abajo Derecha
        centerPosX - halfSideLength - 100, centerPosY - halfSideLength + 180, centerPosZ + halfSideLength, // P5 Abajo Izquierda
        
        // Cara Derecha
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // P2 Arriba Izquierda
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // P8 Arriba Derecha
        centerPosX + halfSideLength, centerPosY - halfSideLength + 180, centerPosZ - halfSideLength, // P6 Abajo Derecha
        centerPosX + halfSideLength, centerPosY - halfSideLength + 180, centerPosZ + halfSideLength, // P4 Abajo Izquierda
        
        // Cara Superior
        centerPosX - halfSideLength - 100, centerPosY + halfSideLength, centerPosZ + halfSideLength, // P1 Arriba Izquierda
        centerPosX - halfSideLength -100, centerPosY + halfSideLength, centerPosZ - halfSideLength, // P7 Arriba Derecha
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // P2 Abajo Derecha
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // P8 Abajo Izquierda
        
        // Cara Inferior
        centerPosX - halfSideLength - 100, centerPosY - halfSideLength + 180, centerPosZ + halfSideLength, // P3 Arriba Izquierda
        centerPosX - halfSideLength - 100, centerPosY - halfSideLength + 180, centerPosZ - halfSideLength, // P5 Arriba Derecha
        centerPosX + halfSideLength, centerPosY - halfSideLength + 180, centerPosZ - halfSideLength, // P4 Abajo Derecha
        centerPosX + halfSideLength, centerPosY - halfSideLength + 180, centerPosZ + halfSideLength  // P6 Abajo Izquierda
    };
    GLfloat colour[] = {
        255.0,0.0,0.0,
        255.0,0.0,0.0,
        255.0,0.0,0.0,
        255.0,0.0,0.0,
        0.0,255.0,0.0,
        0.0,255.0,0.0,
        0.0,255.0,0.0,
        0.0,255.0,0.0,
        128,0.0,128,
        128,0.0,128,
        128,0.0,128,
        128,0.0,128,
        0.0, 0.0, 255.0,
        0.0, 0.0, 255.0,
        0.0, 0.0, 255.0,
        0.0, 0.0, 255.0,
        255.0,255.0,0.0,
        255.0,255.0,0.0,
        255.0,255.0,0.0,
        255.0,255.0,0.0,
        255.0,255.0,255.0,
        255.0,255.0,255.0,
        255.0,255.0,255.0,
        255.0,255.0,255.0,
    };
    
    //    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glEnable(GL_DEPTH_TEST); //Agregar la proyección de profundidad
    glDepthMask(GL_TRUE);//Agregar la proyección de profundidad
    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer( 3, GL_FLOAT, 0, vertices );
    glColorPointer(3, GL_FLOAT, 0, colour); //Buffer de color
    glDrawArrays( GL_QUADS, 0, 24 );
    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState(GL_COLOR_ARRAY);
}

void Pata1( GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength )
{
    GLfloat halfSideLength = edgeLength * 0.5f;
    
    GLfloat vertices[] =
    {
        
        // Cara frontal
        centerPosX - halfSideLength - 100, centerPosY - halfSideLength + 180, centerPosZ + halfSideLength, // P1 Arriba Izquierda
        centerPosX - halfSideLength - 85, centerPosY - halfSideLength + 180, centerPosZ + halfSideLength, // P2 Arriba Derecha
        centerPosX - halfSideLength - 85, centerPosY - halfSideLength + 50, centerPosZ + halfSideLength, // P4 Abajo Derecha
        centerPosX - halfSideLength - 100, centerPosY - halfSideLength + 50, centerPosZ + halfSideLength, // P3 Abajo Izquierda
        
        // Cara Trasera
        centerPosX - halfSideLength - 100, centerPosY - halfSideLength + 180, centerPosZ + halfSideLength - 20, // P7 Arriba Izquierda
        centerPosX - halfSideLength - 85, centerPosY - halfSideLength + 180, centerPosZ + halfSideLength - 20, // P8 Arriba Derecha
        centerPosX - halfSideLength - 85, centerPosY - halfSideLength + 50, centerPosZ + halfSideLength - 20, // P6 Abajo Derecha
        centerPosX - halfSideLength - 100, centerPosY - halfSideLength + 50, centerPosZ + halfSideLength - 20, // P5 Abajo Izquierda
        
        // Cara Izquierda
        centerPosX - halfSideLength - 100, centerPosY - halfSideLength + 180, centerPosZ + halfSideLength - 20, // P7 Arriba Izquierda
        centerPosX - halfSideLength - 100, centerPosY - halfSideLength + 180, centerPosZ + halfSideLength, // P1 Arriba Dereccha
        centerPosX - halfSideLength - 100, centerPosY - halfSideLength + 50, centerPosZ + halfSideLength, // P3 Abajo Derecha
        centerPosX - halfSideLength - 100, centerPosY - halfSideLength + 50, centerPosZ + halfSideLength - 20, // P5 Abajo Izquierda
        
        // Cara Derecha
        centerPosX - halfSideLength - 85, centerPosY - halfSideLength + 180, centerPosZ + halfSideLength, // P2 Arriba Izquierda
        centerPosX - halfSideLength - 85, centerPosY - halfSideLength + 180, centerPosZ + halfSideLength - 20, // P8 Arriba Derecha
        centerPosX - halfSideLength - 85, centerPosY - halfSideLength + 50, centerPosZ + halfSideLength - 20, // P6 Abajo Derecha
        centerPosX - halfSideLength - 85, centerPosY - halfSideLength + 50, centerPosZ + halfSideLength, // P4 Abajo Izquierda
        
        // Cara Superior
        centerPosX - halfSideLength - 100, centerPosY - halfSideLength + 180, centerPosZ + halfSideLength, // P1 Arriba Izquierda
        centerPosX - halfSideLength - 100, centerPosY - halfSideLength + 180, centerPosZ + halfSideLength - 20, // P7 Arriba Derecha
        centerPosX - halfSideLength - 85, centerPosY - halfSideLength + 180, centerPosZ + halfSideLength, // P2 Abajo Derecha
        centerPosX - halfSideLength - 85, centerPosY - halfSideLength + 180, centerPosZ + halfSideLength - 20, // P8 Abajo Izquierda
        
        // Cara Inferior
        centerPosX - halfSideLength - 100, centerPosY - halfSideLength + 50, centerPosZ + halfSideLength, // P3 Arriba Izquierda
        centerPosX - halfSideLength - 100, centerPosY - halfSideLength + 50, centerPosZ + halfSideLength - 20, // P5 Arriba Derecha
        centerPosX - halfSideLength - 85, centerPosY - halfSideLength + 50, centerPosZ + halfSideLength, // P4 Abajo Derecha
        centerPosX - halfSideLength - 85, centerPosY - halfSideLength + 50, centerPosZ + halfSideLength - 20 // P6 Abajo Izquierda
    };
    GLfloat colour[] = {
        255.0,0.0,0.0,
        255.0,0.0,0.0,
        255.0,0.0,0.0,
        255.0,0.0,0.0,
        0.0,255.0,0.0,
        0.0,255.0,0.0,
        0.0,255.0,0.0,
        0.0,255.0,0.0,
        128,0.0,128,
        128,0.0,128,
        128,0.0,128,
        128,0.0,128,
        0.0, 0.0, 255.0,
        0.0, 0.0, 255.0,
        0.0, 0.0, 255.0,
        0.0, 0.0, 255.0,
        255.0,255.0,0.0,
        255.0,255.0,0.0,
        255.0,255.0,0.0,
        255.0,255.0,0.0,
        255.0,255.0,255.0,
        255.0,255.0,255.0,
        255.0,255.0,255.0,
        255.0,255.0,255.0,
    };
    
    //    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glEnable(GL_DEPTH_TEST); //Agregar la proyección de profundidad
    glDepthMask(GL_TRUE);//Agregar la proyección de profundidad
    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer( 3, GL_FLOAT, 0, vertices );
    glColorPointer(3, GL_FLOAT, 0, colour); //Buffer de color
    glDrawArrays( GL_QUADS, 0, 24 );
    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState(GL_COLOR_ARRAY);
}


void Pata2( GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength )
{
    GLfloat halfSideLength = edgeLength * 0.5f;
    
    GLfloat vertices[] =
    {
        
        // Cara frontal
        centerPosX - halfSideLength - 100, centerPosY - halfSideLength + 180, centerPosZ - halfSideLength + 20, // P1 Arriba Izquierda
        centerPosX - halfSideLength - 85, centerPosY - halfSideLength + 180, centerPosZ - halfSideLength + 20, // P2 Arriba Derecha
        centerPosX - halfSideLength - 85, centerPosY - halfSideLength + 50, centerPosZ - halfSideLength + 20, // P4 Abajo Derecha
        centerPosX - halfSideLength - 100, centerPosY - halfSideLength + 50, centerPosZ - halfSideLength + 20, // P3 Abajo Izquierda
        
        // Cara Trasera
        centerPosX - halfSideLength - 100, centerPosY - halfSideLength + 180, centerPosZ - halfSideLength, // P7 Arriba Izquierda
        centerPosX - halfSideLength - 85, centerPosY - halfSideLength + 180, centerPosZ - halfSideLength, // P8 Arriba Derecha
        centerPosX - halfSideLength - 85, centerPosY - halfSideLength + 50, centerPosZ - halfSideLength, // P6 Abajo Derecha
        centerPosX - halfSideLength - 100, centerPosY - halfSideLength + 50, centerPosZ - halfSideLength, // P5 Abajo Izquierda
        
        // Cara Izquierda
        centerPosX - halfSideLength - 100, centerPosY - halfSideLength + 180, centerPosZ - halfSideLength, // P7 Arriba Izquierda
        centerPosX - halfSideLength - 100, centerPosY - halfSideLength + 180, centerPosZ - halfSideLength + 20, // P1 Arriba Dereccha
        centerPosX - halfSideLength - 100, centerPosY - halfSideLength + 50, centerPosZ - halfSideLength + 20, // P3 Abajo Derecha
        centerPosX - halfSideLength - 100, centerPosY - halfSideLength + 50, centerPosZ - halfSideLength, // P5 Abajo Izquierda
        
        // Cara Derecha
        centerPosX - halfSideLength - 85, centerPosY - halfSideLength + 180, centerPosZ - halfSideLength + 20, // P2 Arriba Izquierda
        centerPosX - halfSideLength - 85, centerPosY - halfSideLength + 180, centerPosZ - halfSideLength, // P8 Arriba Derecha
        centerPosX - halfSideLength - 85, centerPosY - halfSideLength + 50, centerPosZ - halfSideLength, // P6 Abajo Derecha
        centerPosX - halfSideLength - 85, centerPosY - halfSideLength + 50, centerPosZ - halfSideLength + 20, // P4 Abajo Izquierda
        
        // Cara Superior
        centerPosX - halfSideLength - 100, centerPosY - halfSideLength + 180, centerPosZ - halfSideLength + 20, // P1 Arriba Izquierda
        centerPosX - halfSideLength - 100, centerPosY - halfSideLength + 180, centerPosZ - halfSideLength, // P7 Arriba Derecha
        centerPosX - halfSideLength - 85, centerPosY - halfSideLength + 180, centerPosZ - halfSideLength + 20, // P2 Abajo Derecha
        centerPosX - halfSideLength - 85, centerPosY - halfSideLength + 180, centerPosZ - halfSideLength, // P8 Abajo Izquierda
        
        // Cara Inferior
        centerPosX - halfSideLength - 100, centerPosY - halfSideLength + 50, centerPosZ - halfSideLength + 20, // P3 Arriba Izquierda
        centerPosX - halfSideLength - 100, centerPosY - halfSideLength + 50, centerPosZ - halfSideLength, // P5 Arriba Derecha
        centerPosX - halfSideLength - 85, centerPosY - halfSideLength + 50, centerPosZ - halfSideLength + 20, // P4 Abajo Derecha
        centerPosX - halfSideLength - 85, centerPosY - halfSideLength + 50, centerPosZ - halfSideLength // P6 Abajo Izquierda
    };
    GLfloat colour[] = {
        255.0,0.0,0.0,
        255.0,0.0,0.0,
        255.0,0.0,0.0,
        255.0,0.0,0.0,
        0.0,255.0,0.0,
        0.0,255.0,0.0,
        0.0,255.0,0.0,
        0.0,255.0,0.0,
        128,0.0,128,
        128,0.0,128,
        128,0.0,128,
        128,0.0,128,
        0.0, 0.0, 255.0,
        0.0, 0.0, 255.0,
        0.0, 0.0, 255.0,
        0.0, 0.0, 255.0,
        255.0,255.0,0.0,
        255.0,255.0,0.0,
        255.0,255.0,0.0,
        255.0,255.0,0.0,
        255.0,255.0,255.0,
        255.0,255.0,255.0,
        255.0,255.0,255.0,
        255.0,255.0,255.0,
    };
    
    //    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glEnable(GL_DEPTH_TEST); //Agregar la proyección de profundidad
    glDepthMask(GL_TRUE);//Agregar la proyección de profundidad
    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer( 3, GL_FLOAT, 0, vertices );
    glColorPointer(3, GL_FLOAT, 0, colour); //Buffer de color
    glDrawArrays( GL_QUADS, 0, 24 );
    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState(GL_COLOR_ARRAY);
}

void Pata3( GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength )
{
    GLfloat halfSideLength = edgeLength * 0.5f;
    
    GLfloat vertices[] =
    {
        
        // Cara frontal
        centerPosX + halfSideLength - 15, centerPosY - halfSideLength + 180, centerPosZ - halfSideLength + 20, // P1 Arriba Izquierda
        centerPosX + halfSideLength, centerPosY - halfSideLength + 180, centerPosZ - halfSideLength + 20, // P2 Arriba Derecha
        centerPosX + halfSideLength, centerPosY - halfSideLength + 50, centerPosZ - halfSideLength + 20,  // P4 Abajo Derecha
        centerPosX + halfSideLength - 15, centerPosY - halfSideLength + 50, centerPosZ - halfSideLength + 20, // P3 Abajo Izquierda
        
        // Cara Trasera
        centerPosX + halfSideLength - 15, centerPosY - halfSideLength + 180, centerPosZ - halfSideLength, // P7 Arriba Izquierda
        centerPosX + halfSideLength, centerPosY - halfSideLength + 180, centerPosZ - halfSideLength, // P8 Arriba Derecha
        centerPosX + halfSideLength, centerPosY - halfSideLength + 50, centerPosZ - halfSideLength, // P6 Abajo Derecha
        centerPosX + halfSideLength - 15, centerPosY - halfSideLength + 50, centerPosZ - halfSideLength, // P5 Abajo Izquierda
        
        // Cara Izquierda
        centerPosX + halfSideLength - 15, centerPosY - halfSideLength + 180, centerPosZ - halfSideLength, // P7 Arriba Izquierda
        centerPosX + halfSideLength - 15, centerPosY - halfSideLength + 180, centerPosZ - halfSideLength + 20, // P1 Arriba Dereccha
        centerPosX + halfSideLength - 15, centerPosY - halfSideLength + 50, centerPosZ - halfSideLength + 20, // P3 Abajo Derecha
        centerPosX + halfSideLength - 15, centerPosY - halfSideLength + 50, centerPosZ - halfSideLength, // P5 Abajo Izquierda
        
        // Cara Derecha
        centerPosX + halfSideLength, centerPosY - halfSideLength + 180, centerPosZ - halfSideLength + 20, // P2 Arriba Izquierda
        centerPosX + halfSideLength, centerPosY - halfSideLength + 180, centerPosZ - halfSideLength, // P8 Arriba Derecha
        centerPosX + halfSideLength, centerPosY - halfSideLength + 50, centerPosZ - halfSideLength, // P6 Abajo Derecha
        centerPosX + halfSideLength, centerPosY - halfSideLength + 50, centerPosZ - halfSideLength + 20, // P4 Abajo Izquierda
        
        // Cara Superior
        centerPosX + halfSideLength - 15, centerPosY - halfSideLength + 180, centerPosZ - halfSideLength + 20, // P1 Arriba Izquierda
        centerPosX + halfSideLength - 15, centerPosY - halfSideLength + 180, centerPosZ - halfSideLength, // P7 Arriba Derecha
        centerPosX + halfSideLength, centerPosY - halfSideLength + 180, centerPosZ - halfSideLength + 20, // P2 Abajo Derecha
        centerPosX + halfSideLength, centerPosY - halfSideLength + 180, centerPosZ - halfSideLength, // P8 Abajo Izquierda
        
        // Cara Inferior
        centerPosX + halfSideLength - 15, centerPosY - halfSideLength + 50, centerPosZ - halfSideLength + 20, // P3 Arriba Izquierda
        centerPosX + halfSideLength - 15, centerPosY - halfSideLength + 50, centerPosZ - halfSideLength, // P5 Arriba Derecha
        centerPosX + halfSideLength, centerPosY - halfSideLength + 50, centerPosZ - halfSideLength + 20,  // P4 Abajo Derecha
        centerPosX + halfSideLength, centerPosY - halfSideLength + 50, centerPosZ - halfSideLength // P6 Abajo Izquierda
    };
    GLfloat colour[] = {
        255.0,0.0,0.0,
        255.0,0.0,0.0,
        255.0,0.0,0.0,
        255.0,0.0,0.0,
        0.0,255.0,0.0,
        0.0,255.0,0.0,
        0.0,255.0,0.0,
        0.0,255.0,0.0,
        128,0.0,128,
        128,0.0,128,
        128,0.0,128,
        128,0.0,128,
        0.0, 0.0, 255.0,
        0.0, 0.0, 255.0,
        0.0, 0.0, 255.0,
        0.0, 0.0, 255.0,
        255.0,255.0,0.0,
        255.0,255.0,0.0,
        255.0,255.0,0.0,
        255.0,255.0,0.0,
        255.0,255.0,255.0,
        255.0,255.0,255.0,
        255.0,255.0,255.0,
        255.0,255.0,255.0,
    };
    
    //    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glEnable(GL_DEPTH_TEST); //Agregar la proyección de profundidad
    glDepthMask(GL_TRUE);//Agregar la proyección de profundidad
    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer( 3, GL_FLOAT, 0, vertices );
    glColorPointer(3, GL_FLOAT, 0, colour); //Buffer de color
    glDrawArrays( GL_QUADS, 0, 24 );
    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState(GL_COLOR_ARRAY);
}

void Pata4( GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength )
{
    GLfloat halfSideLength = edgeLength * 0.5f;
    
    GLfloat vertices[] =
    {
        
        // Cara frontal
        centerPosX + halfSideLength - 15, centerPosY - halfSideLength + 180, centerPosZ + halfSideLength, // P1 Arriba Izquierda
        centerPosX + halfSideLength, centerPosY - halfSideLength + 180, centerPosZ + halfSideLength,  // P2 Arriba Derecha
        centerPosX + halfSideLength, centerPosY - halfSideLength + 50, centerPosZ + halfSideLength, // P4 Abajo Derecha
        centerPosX + halfSideLength - 15, centerPosY - halfSideLength + 50, centerPosZ + halfSideLength, // P3 Abajo Izquierda
        
        // Cara Trasera
        centerPosX + halfSideLength - 15, centerPosY - halfSideLength + 180, centerPosZ + halfSideLength - 20,  // P7 Arriba Izquierda
        centerPosX + halfSideLength, centerPosY - halfSideLength + 180, centerPosZ + halfSideLength - 20,  // P8 Arriba Derecha
        centerPosX + halfSideLength, centerPosY - halfSideLength + 50, centerPosZ + halfSideLength - 20,  // P6 Abajo Derecha
        centerPosX + halfSideLength - 15, centerPosY - halfSideLength + 50, centerPosZ + halfSideLength - 20, // P5 Abajo Izquierda
        
        // Cara Izquierda
        centerPosX + halfSideLength - 15, centerPosY - halfSideLength + 180, centerPosZ + halfSideLength - 20, // P7 Arriba Izquierda
        centerPosX + halfSideLength - 15, centerPosY - halfSideLength + 180, centerPosZ + halfSideLength, // P1 Arriba Dereccha
        centerPosX + halfSideLength - 15, centerPosY - halfSideLength + 50, centerPosZ + halfSideLength, // P3 Abajo Derecha
        centerPosX + halfSideLength - 15, centerPosY - halfSideLength + 50, centerPosZ + halfSideLength - 20, // P5 Abajo Izquierda
        
        // Cara Derecha
        centerPosX + halfSideLength, centerPosY - halfSideLength + 180, centerPosZ + halfSideLength,  // P2 Arriba Izquierda
        centerPosX + halfSideLength, centerPosY - halfSideLength + 180, centerPosZ + halfSideLength - 20, // P8 Arriba Derecha
        centerPosX + halfSideLength, centerPosY - halfSideLength + 50, centerPosZ + halfSideLength - 20,  // P6 Abajo Derecha
        centerPosX + halfSideLength, centerPosY - halfSideLength + 50, centerPosZ + halfSideLength,  // P4 Abajo Izquierda
        
        // Cara Superior
        centerPosX + halfSideLength - 15, centerPosY - halfSideLength + 180, centerPosZ + halfSideLength, // P1 Arriba Izquierda
        centerPosX + halfSideLength - 15, centerPosY - halfSideLength + 180, centerPosZ + halfSideLength - 20, // P7 Arriba Derecha
        centerPosX + halfSideLength, centerPosY - halfSideLength + 180, centerPosZ + halfSideLength,  // P2 Abajo Derecha
        centerPosX + halfSideLength, centerPosY - halfSideLength + 180, centerPosZ + halfSideLength - 20, // P8 Abajo Izquierda
        
        // Cara Inferior
        centerPosX + halfSideLength - 15, centerPosY - halfSideLength + 50, centerPosZ + halfSideLength, // P3 Arriba Izquierda
        centerPosX + halfSideLength - 15, centerPosY - halfSideLength + 50, centerPosZ + halfSideLength - 20, // P5 Arriba Derecha
        centerPosX + halfSideLength, centerPosY - halfSideLength + 50, centerPosZ + halfSideLength,  // P4 Abajo Derecha
        centerPosX + halfSideLength, centerPosY - halfSideLength + 50, centerPosZ + halfSideLength - 20  // P6 Abajo Izquierda
    };
    GLfloat colour[] = {
        255.0,0.0,0.0,
        255.0,0.0,0.0,
        255.0,0.0,0.0,
        255.0,0.0,0.0,
        0.0,255.0,0.0,
        0.0,255.0,0.0,
        0.0,255.0,0.0,
        0.0,255.0,0.0,
        128,0.0,128,
        128,0.0,128,
        128,0.0,128,
        128,0.0,128,
        0.0, 0.0, 255.0,
        0.0, 0.0, 255.0,
        0.0, 0.0, 255.0,
        0.0, 0.0, 255.0,
        255.0,255.0,0.0,
        255.0,255.0,0.0,
        255.0,255.0,0.0,
        255.0,255.0,0.0,
        255.0,255.0,255.0,
        255.0,255.0,255.0,
        255.0,255.0,255.0,
        255.0,255.0,255.0,
    };
    
    //    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glEnable(GL_DEPTH_TEST); //Agregar la proyección de profundidad
    glDepthMask(GL_TRUE);//Agregar la proyección de profundidad
    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer( 3, GL_FLOAT, 0, vertices );
    glColorPointer(3, GL_FLOAT, 0, colour); //Buffer de color
    glDrawArrays( GL_QUADS, 0, 24 );
    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState(GL_COLOR_ARRAY);
}

