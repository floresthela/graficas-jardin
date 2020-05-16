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

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

void keyCallback( GLFWwindow *window, int key, int scancode, int action, int mods );

// figuras para la fuente
void base(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength);
void lado1(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength);
void lado2(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength);
void lado3(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength);
void lado4(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength);
void centro(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength);
void top(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength);

void piso(GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength);

GLfloat rotationX = 0.0f;
GLfloat rotationY = 0.0f;
//GLfloat translationX = 0.0f;
//GLfloat translationY = 0.0f;
GLfloat escalar = 1.0f;

int main(void) {
    GLFWwindow *window;
    
    // Inicializar la librería
    if (!glfwInit()){
        return -1;
    }
    
    // Crear la ventana
    window = glfwCreateWindow( SCREEN_WIDTH, SCREEN_HEIGHT, "Proyecto Final", NULL, NULL );
    
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
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);
        
        // Render (Se crea el cubo y se generan los cambios en los vectores de transformación
        glPushMatrix();
        glTranslatef(halfScreenWidth, halfScreenHeight, -500);
        glScalef(escalar, escalar, escalar);
        
        glRotatef( rotationX, 1, 0, 0 ); // Rotar el cubo en X
        glRotatef( rotationY, 0, 1, 0 ); // Rotar el cubo en Y
        glTranslatef( -halfScreenWidth, -halfScreenHeight, 500 );
        
        base(halfScreenWidth, halfScreenHeight, -500, 200);
        lado1(halfScreenWidth, halfScreenHeight + 40, -500, 200);
        
        lado2(halfScreenWidth + 220 , halfScreenHeight + 40, -500, 200);
        lado3(halfScreenWidth, halfScreenHeight + 40, -500, 200);
        lado3(halfScreenWidth, halfScreenHeight + 40, -280, 200);
        
        centro(halfScreenWidth + 95, halfScreenHeight, -400, 200);
        top(halfScreenWidth + 170, halfScreenHeight + 50, -440, 200);
        
        piso(halfScreenWidth, halfScreenHeight + 880, -500, 200);
        
        
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
//            case GLFW_KEY_A:
//                translationX -= 10;
//                break;
//            case GLFW_KEY_S:
//                translationX += 10;
//                break;
//            case GLFW_KEY_W:
//                translationY += 10;
//                break;
//            case GLFW_KEY_X:
//                translationY -=10;
//                break;
            case GLFW_KEY_1: // escalar disminuye el tamaño con la tecla del número 1
                escalar -= 0.1;
                break;
            case GLFW_KEY_2: // escalar aumenta el tamaño con la tecla del número 2
                escalar += 0.1;
                break;
        }
        
        
    }
}


void base( GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength )
{
    GLfloat halfSideLength = edgeLength * 0.6f;
    int h1 = 230;
    GLfloat vertices[] =
    {
        // Cara frontal
        centerPosX - halfSideLength, centerPosY + halfSideLength - h1, centerPosZ + halfSideLength, // P1
        centerPosX + halfSideLength, centerPosY + halfSideLength - h1, centerPosZ + halfSideLength, // P2
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // P4
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // P3
        
        // Cara Trasera
        centerPosX - halfSideLength, centerPosY + halfSideLength - h1, centerPosZ - halfSideLength, // P7
        centerPosX + halfSideLength, centerPosY + halfSideLength - h1, centerPosZ - halfSideLength, // P8
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // P6
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // P5
        
        // Cara Izquierda
        centerPosX - halfSideLength, centerPosY + halfSideLength - h1, centerPosZ + halfSideLength, // P7
        centerPosX - halfSideLength, centerPosY + halfSideLength - h1, centerPosZ - halfSideLength, // P1
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // P3
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // P5
        
        // Cara Derecha
        centerPosX + halfSideLength, centerPosY + halfSideLength - h1, centerPosZ + halfSideLength, // P2
        centerPosX + halfSideLength, centerPosY + halfSideLength - h1, centerPosZ - halfSideLength, // P8
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // P6
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // P4
        
        // Cara Superior
        centerPosX - halfSideLength, centerPosY + halfSideLength - h1, centerPosZ + halfSideLength, // P1
        centerPosX - halfSideLength, centerPosY + halfSideLength - h1, centerPosZ - halfSideLength, // P7
        centerPosX + halfSideLength, centerPosY + halfSideLength - h1, centerPosZ - halfSideLength, // P2
        centerPosX + halfSideLength, centerPosY + halfSideLength - h1, centerPosZ + halfSideLength, // P8
        
        // Cara Inferior
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // P3
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // P5
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // P4
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength  // P6
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
        
        255.0,255.0,255.0,
        255.0,255.0,255.0,
        255.0,255.0,255.0,
        255.0,255.0,255.0,
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

void lado1( GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength )
{
    GLfloat halfSideLength = edgeLength * 0.6f;
    int h1 = -100, h2 = 240, h3 = 30;
    
    GLfloat vertices[] =
    {
        // Cara frontal
        centerPosX - halfSideLength, centerPosY + halfSideLength - h2, centerPosZ + halfSideLength, // P1
        centerPosX + h1, centerPosY + halfSideLength - h2, centerPosZ + halfSideLength, // P2
        centerPosX + h1, centerPosY - halfSideLength - h3, centerPosZ + halfSideLength, // P4
        centerPosX - halfSideLength, centerPosY - halfSideLength - h3, centerPosZ + halfSideLength, // P3
        
        // Cara Trasera
        centerPosX - halfSideLength, centerPosY + halfSideLength - h2, centerPosZ - halfSideLength, // P7
         centerPosX + h1, centerPosY + halfSideLength - h2, centerPosZ - halfSideLength, // P8
         centerPosX + h1, centerPosY - halfSideLength - h3, centerPosZ - halfSideLength, // P6
        centerPosX - halfSideLength, centerPosY - halfSideLength - h3, centerPosZ - halfSideLength, // P5
        
        // Cara Izquierda
        centerPosX - halfSideLength, centerPosY + halfSideLength - h2, centerPosZ + halfSideLength, // P7
        centerPosX - halfSideLength, centerPosY + halfSideLength - h2, centerPosZ - halfSideLength, // P1
        centerPosX - halfSideLength, centerPosY - halfSideLength - h3, centerPosZ - halfSideLength, // P3
        centerPosX - halfSideLength, centerPosY - halfSideLength - h3, centerPosZ + halfSideLength, // P5
        
        // Cara Derecha
         centerPosX + h1, centerPosY + halfSideLength - h2, centerPosZ + halfSideLength, // P2
         centerPosX + h1, centerPosY + halfSideLength - h2, centerPosZ - halfSideLength, // P8
         centerPosX + h1, centerPosY - halfSideLength - h3, centerPosZ - halfSideLength, // P6
         centerPosX + h1, centerPosY - halfSideLength - h3, centerPosZ + halfSideLength, // P4
        
        // Cara Superior
        centerPosX - halfSideLength, centerPosY + halfSideLength - h2, centerPosZ + halfSideLength, // P1
        centerPosX - halfSideLength, centerPosY + halfSideLength - h2, centerPosZ - halfSideLength, // P7
         centerPosX + h1, centerPosY + halfSideLength - h2, centerPosZ - halfSideLength, // P2
         centerPosX + h1, centerPosY + halfSideLength - h2, centerPosZ + halfSideLength, // P8
        
        // Cara Inferior
        centerPosX - halfSideLength, centerPosY - halfSideLength - h3, centerPosZ + halfSideLength, // P3
        centerPosX - halfSideLength, centerPosY - halfSideLength - h3, centerPosZ - halfSideLength, // P5
         centerPosX + h1, centerPosY - halfSideLength - h3, centerPosZ - halfSideLength, // P4
         centerPosX + h1, centerPosY - halfSideLength - h3, centerPosZ + halfSideLength  // P6
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
        
        255.0,255.0,255.0,
        255.0,255.0,255.0,
        255.0,255.0,255.0,
        255.0,255.0,255.0,
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


void lado2( GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength )
{
    GLfloat halfSideLength = edgeLength * 0.6f;
    int h1 = -100, h2 = 240, h3 = 30;
    
    GLfloat vertices[] =
    {
        // Cara frontal
        centerPosX - halfSideLength, centerPosY + halfSideLength - h2, centerPosZ + halfSideLength, // P1
        centerPosX + h1, centerPosY + halfSideLength - h2, centerPosZ + halfSideLength, // P2
        centerPosX + h1, centerPosY - halfSideLength - h3, centerPosZ + halfSideLength, // P4
        centerPosX - halfSideLength, centerPosY - halfSideLength - h3, centerPosZ + halfSideLength, // P3
        
        // Cara Trasera
        centerPosX - halfSideLength, centerPosY + halfSideLength - h2, centerPosZ - halfSideLength, // P7
        centerPosX + h1, centerPosY + halfSideLength - h2, centerPosZ - halfSideLength, // P8
        centerPosX + h1, centerPosY - halfSideLength - h3, centerPosZ - halfSideLength, // P6
        centerPosX - halfSideLength, centerPosY - halfSideLength - h3, centerPosZ - halfSideLength, // P5
        
        // Cara Izquierda
        centerPosX - halfSideLength, centerPosY + halfSideLength - h2, centerPosZ + halfSideLength, // P7
        centerPosX - halfSideLength, centerPosY + halfSideLength - h2, centerPosZ - halfSideLength, // P1
        centerPosX - halfSideLength, centerPosY - halfSideLength - h3, centerPosZ - halfSideLength, // P3
        centerPosX - halfSideLength, centerPosY - halfSideLength - h3, centerPosZ + halfSideLength, // P5
        
        // Cara Derecha
        centerPosX + h1, centerPosY + halfSideLength - h2, centerPosZ + halfSideLength, // P2
        centerPosX + h1, centerPosY + halfSideLength - h2, centerPosZ - halfSideLength, // P8
        centerPosX + h1, centerPosY - halfSideLength - h3, centerPosZ - halfSideLength, // P6
        centerPosX + h1, centerPosY - halfSideLength - h3, centerPosZ + halfSideLength, // P4
        
        // Cara Superior
        centerPosX - halfSideLength, centerPosY + halfSideLength - h2, centerPosZ + halfSideLength, // P1
        centerPosX - halfSideLength, centerPosY + halfSideLength - h2, centerPosZ - halfSideLength, // P7
        centerPosX + h1, centerPosY + halfSideLength - h2, centerPosZ - halfSideLength, // P2
        centerPosX + h1, centerPosY + halfSideLength - h2, centerPosZ + halfSideLength, // P8
        
        // Cara Inferior
        centerPosX - halfSideLength, centerPosY - halfSideLength - h3, centerPosZ + halfSideLength, // P3
        centerPosX - halfSideLength, centerPosY - halfSideLength - h3, centerPosZ - halfSideLength, // P5
        centerPosX + h1, centerPosY - halfSideLength - h3, centerPosZ - halfSideLength, // P4
        centerPosX + h1, centerPosY - halfSideLength - h3, centerPosZ + halfSideLength  // P6
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
        
        255.0,255.0,255.0,
        255.0,255.0,255.0,
        255.0,255.0,255.0,
        255.0,255.0,255.0,
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

void lado3( GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength )
{
    GLfloat halfSideLength = edgeLength * 0.6f;
    int h1 = 120, h2 = 240, h3 = 30, z1 = 220, x1 = 100;
    
    GLfloat vertices[] =
    {
        // Cara frontal
        centerPosX - halfSideLength, centerPosY + halfSideLength - h2, centerPosZ + halfSideLength - z1, // P1
        centerPosX + h1, centerPosY + halfSideLength - h2, centerPosZ + halfSideLength - z1, // P2
        centerPosX + h1, centerPosY - halfSideLength - h3, centerPosZ + halfSideLength - z1, // P4
        centerPosX - halfSideLength, centerPosY - halfSideLength - h3, centerPosZ + halfSideLength - z1, // P3
        
        // Cara Trasera
        centerPosX - halfSideLength, centerPosY + halfSideLength - h2, centerPosZ - halfSideLength, // P7
        centerPosX + h1, centerPosY + halfSideLength - h2, centerPosZ - halfSideLength, // P8
        centerPosX + h1, centerPosY - halfSideLength - h3, centerPosZ - halfSideLength, // P6
        centerPosX - halfSideLength, centerPosY - halfSideLength - h3, centerPosZ - halfSideLength, // P5
        
        // Cara Izquierda
        centerPosX - halfSideLength, centerPosY + halfSideLength - h2, centerPosZ + halfSideLength - z1, // P7 ... P1
        centerPosX - halfSideLength, centerPosY + halfSideLength - h2, centerPosZ - halfSideLength, // P1 o P7
        centerPosX - halfSideLength, centerPosY - halfSideLength - h3, centerPosZ - halfSideLength, // P3 -> P5
        centerPosX - halfSideLength, centerPosY - halfSideLength - h3, centerPosZ + halfSideLength - z1, // P5 -> P3
        
        // Cara Derecha
        centerPosX + h1, centerPosY + halfSideLength - h2, centerPosZ + halfSideLength - z1, // P2
        centerPosX + h1, centerPosY + halfSideLength - h2, centerPosZ - halfSideLength, // P8
        centerPosX + h1, centerPosY - halfSideLength - h3, centerPosZ - halfSideLength, // P6
        centerPosX + h1, centerPosY - halfSideLength - h3, centerPosZ + halfSideLength - z1, // P4
        
        // Cara Superior
        centerPosX - halfSideLength, centerPosY + halfSideLength - h2, centerPosZ + halfSideLength - z1, // P1
        centerPosX - halfSideLength, centerPosY + halfSideLength - h2, centerPosZ - halfSideLength, // P7
        centerPosX + h1, centerPosY + halfSideLength - h2, centerPosZ - halfSideLength, // P2 ... P8
        centerPosX + h1, centerPosY + halfSideLength - h2, centerPosZ + halfSideLength - z1, // P8 ... P2
        
        // Cara Inferior
        centerPosX - halfSideLength, centerPosY - halfSideLength - h3, centerPosZ + halfSideLength - z1, // P3
        centerPosX - halfSideLength, centerPosY - halfSideLength - h3, centerPosZ - halfSideLength, // P5
        centerPosX + h1, centerPosY - halfSideLength - h3, centerPosZ - halfSideLength, // P4
        centerPosX + h1, centerPosY - halfSideLength - h3, centerPosZ + halfSideLength - z1  // P6
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
        
        255.0,255.0,255.0,
        255.0,255.0,255.0,
        255.0,255.0,255.0,
        255.0,255.0,255.0,
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

void lado4( GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength )
{
    GLfloat halfSideLength = edgeLength * 0.6f;
    int h1 = 120, h2 = 240, h3 = 30, z1 = 220, x1 = 100;
    
    GLfloat vertices[] =
    {
        // Cara frontal
        centerPosX - halfSideLength, centerPosY + halfSideLength - h2, centerPosZ + halfSideLength - z1, // P1
        centerPosX + h1, centerPosY + halfSideLength - h2, centerPosZ + halfSideLength - z1, // P2
        centerPosX + h1, centerPosY - halfSideLength - h3, centerPosZ + halfSideLength - z1, // P4
        centerPosX - halfSideLength, centerPosY - halfSideLength - h3, centerPosZ + halfSideLength - z1, // P3
        
        // Cara Trasera
        centerPosX - halfSideLength, centerPosY + halfSideLength - h2, centerPosZ - halfSideLength, // P7
        centerPosX + h1, centerPosY + halfSideLength - h2, centerPosZ - halfSideLength, // P8
        centerPosX + h1, centerPosY - halfSideLength - h3, centerPosZ - halfSideLength, // P6
        centerPosX - halfSideLength, centerPosY - halfSideLength - h3, centerPosZ - halfSideLength, // P5
        
        // Cara Izquierda
        centerPosX - halfSideLength, centerPosY + halfSideLength - h2, centerPosZ + halfSideLength - z1, // P7 ... P1
        centerPosX - halfSideLength, centerPosY + halfSideLength - h2, centerPosZ - halfSideLength, // P1 o P7
        centerPosX - halfSideLength, centerPosY - halfSideLength - h3, centerPosZ - halfSideLength, // P3 -> P5
        centerPosX - halfSideLength, centerPosY - halfSideLength - h3, centerPosZ + halfSideLength - z1, // P5 -> P3
        
        // Cara Derecha
        centerPosX + h1, centerPosY + halfSideLength - h2, centerPosZ + halfSideLength - z1, // P2
        centerPosX + h1, centerPosY + halfSideLength - h2, centerPosZ - halfSideLength, // P8
        centerPosX + h1, centerPosY - halfSideLength - h3, centerPosZ - halfSideLength, // P6
        centerPosX + h1, centerPosY - halfSideLength - h3, centerPosZ + halfSideLength - z1, // P4
        
        // Cara Superior
        centerPosX - halfSideLength, centerPosY + halfSideLength - h2, centerPosZ + halfSideLength - z1, // P1
        centerPosX - halfSideLength, centerPosY + halfSideLength - h2, centerPosZ - halfSideLength, // P7
        centerPosX + h1, centerPosY + halfSideLength - h2, centerPosZ - halfSideLength, // P2 ... P8
        centerPosX + h1, centerPosY + halfSideLength - h2, centerPosZ + halfSideLength - z1, // P8 ... P2
        
        // Cara Inferior
        centerPosX - halfSideLength, centerPosY - halfSideLength - h3, centerPosZ + halfSideLength - z1, // P3
        centerPosX - halfSideLength, centerPosY - halfSideLength - h3, centerPosZ - halfSideLength, // P5
        centerPosX + h1, centerPosY - halfSideLength - h3, centerPosZ - halfSideLength, // P4
        centerPosX + h1, centerPosY - halfSideLength - h3, centerPosZ + halfSideLength - z1  // P6
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
        
        255.0,255.0,255.0,
        255.0,255.0,255.0,
        255.0,255.0,255.0,
        255.0,255.0,255.0,
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

void centro( GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength )
{
    GLfloat halfSideLength = edgeLength * 0.6f;
    int h1 = -80, h2 = 30, h3 = 0, z1 = 200, x1 = 0;
    
    GLfloat vertices[] =
    {
        // Cara frontal
        centerPosX - halfSideLength, centerPosY + halfSideLength - h2, centerPosZ + halfSideLength - z1, // P1
        centerPosX + h1, centerPosY + halfSideLength - h2, centerPosZ + halfSideLength - z1, // P2
        centerPosX + h1, centerPosY - halfSideLength - h3, centerPosZ + halfSideLength - z1, // P4
        centerPosX - halfSideLength, centerPosY - halfSideLength - h3, centerPosZ + halfSideLength - z1, // P3
        
        // Cara Trasera
        centerPosX - halfSideLength, centerPosY + halfSideLength - h2, centerPosZ - halfSideLength, // P7
        centerPosX + h1, centerPosY + halfSideLength - h2, centerPosZ - halfSideLength, // P8
        centerPosX + h1, centerPosY - halfSideLength - h3, centerPosZ - halfSideLength, // P6
        centerPosX - halfSideLength, centerPosY - halfSideLength - h3, centerPosZ - halfSideLength, // P5
        
        // Cara Izquierda
        centerPosX - halfSideLength, centerPosY + halfSideLength - h2, centerPosZ + halfSideLength - z1, // P7 ... P1
        centerPosX - halfSideLength, centerPosY + halfSideLength - h2, centerPosZ - halfSideLength, // P1 o P7
        centerPosX - halfSideLength, centerPosY - halfSideLength - h3, centerPosZ - halfSideLength, // P3 -> P5
        centerPosX - halfSideLength, centerPosY - halfSideLength - h3, centerPosZ + halfSideLength - z1, // P5 -> P3
        
        // Cara Derecha
        centerPosX + h1, centerPosY + halfSideLength - h2, centerPosZ + halfSideLength - z1, // P2
        centerPosX + h1, centerPosY + halfSideLength - h2, centerPosZ - halfSideLength, // P8
        centerPosX + h1, centerPosY - halfSideLength - h3, centerPosZ - halfSideLength, // P6
        centerPosX + h1, centerPosY - halfSideLength - h3, centerPosZ + halfSideLength - z1, // P4
        
        // Cara Superior
        centerPosX - halfSideLength, centerPosY + halfSideLength - h2, centerPosZ + halfSideLength - z1, // P1
        centerPosX - halfSideLength, centerPosY + halfSideLength - h2, centerPosZ - halfSideLength, // P7
        centerPosX + h1, centerPosY + halfSideLength - h2, centerPosZ - halfSideLength, // P2 ... P8
        centerPosX + h1, centerPosY + halfSideLength - h2, centerPosZ + halfSideLength - z1, // P8 ... P2
        
        // Cara Inferior
        centerPosX - halfSideLength, centerPosY - halfSideLength - h3, centerPosZ + halfSideLength - z1, // P3
        centerPosX - halfSideLength, centerPosY - halfSideLength - h3, centerPosZ - halfSideLength, // P5
        centerPosX + h1, centerPosY - halfSideLength - h3, centerPosZ - halfSideLength, // P4
        centerPosX + h1, centerPosY - halfSideLength - h3, centerPosZ + halfSideLength - z1  // P6
    };
    GLfloat colour[] = {
        255.0,255.0,0,
        255.0,255.0,0,
        255.0,255.0,0,
        255.0,255.0,0,
        255.0,255.0,0,
        255.0,255.0,0,
        255.0,255.0,0,
        255.0,255.0,0,
        255.0,255.0,0,
        255.0,255.0,0,
        255.0,255.0,0,
        255.0,255.0,0,
        255.0,255.0,0,
        255.0,255.0,0,
        255.0,255.0,0,
        255.0,255.0,0,
        
        255.0,255.0,0,
        255.0,255.0,0,
        255.0,255.0,0,
        255.0,255.0,0,
        255.0,255.0,0,
        255.0,255.0,0,
        255.0,255.0,0,
        255.0,255.0,0,
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

void top( GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength )
{
    GLfloat halfSideLength = edgeLength * 0.6f;
    int h1 = -230, h2 = 140, h3 = -90, z1 = 120, x1 = 0;
    
    
    // h1 sube z1 baja
    GLfloat vertices[] =
    {
        // Cara frontal
        centerPosX - halfSideLength, centerPosY + halfSideLength - h2, centerPosZ + halfSideLength - z1, // P1
        centerPosX + h1, centerPosY + halfSideLength - h2, centerPosZ + halfSideLength - z1, // P2
        centerPosX + h1, centerPosY - halfSideLength - h3, centerPosZ + halfSideLength - z1, // P4
        centerPosX - halfSideLength, centerPosY - halfSideLength - h3, centerPosZ + halfSideLength - z1, // P3
        
        // Cara Trasera
        centerPosX - halfSideLength, centerPosY + halfSideLength - h2, centerPosZ - halfSideLength, // P7
        centerPosX + h1, centerPosY + halfSideLength - h2, centerPosZ - halfSideLength, // P8
        centerPosX + h1, centerPosY - halfSideLength - h3, centerPosZ - halfSideLength, // P6
        centerPosX - halfSideLength, centerPosY - halfSideLength - h3, centerPosZ - halfSideLength, // P5
        
        // Cara Izquierda
        centerPosX - halfSideLength, centerPosY + halfSideLength - h2, centerPosZ + halfSideLength - z1, // P7 ... P1
        centerPosX - halfSideLength, centerPosY + halfSideLength - h2, centerPosZ - halfSideLength, // P1 o P7
        centerPosX - halfSideLength, centerPosY - halfSideLength - h3, centerPosZ - halfSideLength, // P3 -> P5
        centerPosX - halfSideLength, centerPosY - halfSideLength - h3, centerPosZ + halfSideLength - z1, // P5 -> P3
        
        // Cara Derecha
        centerPosX + h1, centerPosY + halfSideLength - h2, centerPosZ + halfSideLength - z1, // P2
        centerPosX + h1, centerPosY + halfSideLength - h2, centerPosZ - halfSideLength, // P8
        centerPosX + h1, centerPosY - halfSideLength - h3, centerPosZ - halfSideLength, // P6
        centerPosX + h1, centerPosY - halfSideLength - h3, centerPosZ + halfSideLength - z1, // P4
        
        // Cara Superior
        centerPosX - halfSideLength, centerPosY + halfSideLength - h2, centerPosZ + halfSideLength - z1, // P1
        centerPosX - halfSideLength, centerPosY + halfSideLength - h2, centerPosZ - halfSideLength, // P7
        centerPosX + h1, centerPosY + halfSideLength - h2, centerPosZ - halfSideLength, // P2 ... P8
        centerPosX + h1, centerPosY + halfSideLength - h2, centerPosZ + halfSideLength - z1, // P8 ... P2
        
        // Cara Inferior
        centerPosX - halfSideLength, centerPosY - halfSideLength - h3, centerPosZ + halfSideLength - z1, // P3
        centerPosX - halfSideLength, centerPosY - halfSideLength - h3, centerPosZ - halfSideLength, // P5
        centerPosX + h1, centerPosY - halfSideLength - h3, centerPosZ - halfSideLength, // P4
        centerPosX + h1, centerPosY - halfSideLength - h3, centerPosZ + halfSideLength - z1  // P6
    };
    GLfloat colour[] = {
        255.0,255.0,0,
        255.0,255.0,0,
        255.0,255.0,0,
        255.0,255.0,0,
        
        255.0,0,0,
        255.0,0,0,
        255.0,0,0,
        255.0,0,0,
        
        0,255.0,0,
        0,255.0,0,
        0,255.0,0,
        0,255.0,0,
        
        0,0,255.0,
        0,0,255.0,
        0,0,255.0,
        0,0,255.0,
        
        0,0,255.0,
        0,0,255.0,
        0,0,255.0,
        0,0,255.0,
        
        255.0,255.0,0,
        255.0,255.0,0,
        255.0,255.0,0,
        255.0,255.0,0,
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

void piso( GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength )
{
    GLfloat halfSideLength = edgeLength * 3;
    int h1 = 1600, h2 = 400, h3 = -90, z1 = 120, x1 = 0;
    
    
    // h1 sube z1 baja
    GLfloat vertices[] =
    {
        // Cara frontal
        centerPosX - halfSideLength * 4, centerPosY + halfSideLength - h1, centerPosZ + halfSideLength * 4, // P1
        centerPosX + halfSideLength * 4, centerPosY + halfSideLength - h1, centerPosZ + halfSideLength * 4, // P2
        centerPosX + halfSideLength * 4, centerPosY - halfSideLength - h2, centerPosZ + halfSideLength * 4, // P4
        centerPosX - halfSideLength * 4, centerPosY - halfSideLength - h2, centerPosZ + halfSideLength * 4, // P3
        
        // Cara Trasera
        centerPosX - halfSideLength * 4, centerPosY + halfSideLength - h1, centerPosZ - halfSideLength * 4, // P7
        centerPosX + halfSideLength * 4, centerPosY + halfSideLength - h1, centerPosZ - halfSideLength * 4, // P8
        centerPosX + halfSideLength * 4, centerPosY - halfSideLength - h2, centerPosZ - halfSideLength * 4, // P6
        centerPosX - halfSideLength * 4, centerPosY - halfSideLength - h2, centerPosZ - halfSideLength * 4, // P5
        
        // Cara Izquierda
        centerPosX - halfSideLength * 4, centerPosY + halfSideLength - h1, centerPosZ + halfSideLength * 4, // P7
        centerPosX - halfSideLength * 4, centerPosY + halfSideLength - h1, centerPosZ - halfSideLength * 4, // P1
        centerPosX - halfSideLength * 4, centerPosY - halfSideLength - h2, centerPosZ - halfSideLength * 4, // P3
        centerPosX - halfSideLength * 4, centerPosY - halfSideLength - h2, centerPosZ + halfSideLength * 4, // P5
        
        // Cara Derecha
        centerPosX + halfSideLength * 4, centerPosY + halfSideLength - h1, centerPosZ + halfSideLength * 4, // P2
        centerPosX + halfSideLength * 4, centerPosY + halfSideLength - h1, centerPosZ - halfSideLength * 4, // P8
        centerPosX + halfSideLength * 4, centerPosY - halfSideLength - h2, centerPosZ - halfSideLength * 4, // P6
        centerPosX + halfSideLength * 4, centerPosY - halfSideLength - h2, centerPosZ + halfSideLength * 4, // P4
        
        // Cara Superior
        centerPosX - halfSideLength * 4, centerPosY + halfSideLength - h1, centerPosZ + halfSideLength * 4, // P1
        centerPosX - halfSideLength * 4, centerPosY + halfSideLength - h1, centerPosZ - halfSideLength * 4, // P7
        centerPosX + halfSideLength * 4, centerPosY + halfSideLength - h1, centerPosZ - halfSideLength * 4, // P2
        centerPosX + halfSideLength * 4, centerPosY + halfSideLength - h1, centerPosZ + halfSideLength * 4, // P8
        
        // Cara Inferior
        centerPosX - halfSideLength * 4, centerPosY - halfSideLength - h2, centerPosZ + halfSideLength * 4, // P3
        centerPosX - halfSideLength * 4, centerPosY - halfSideLength - h2, centerPosZ - halfSideLength * 4, // P5
        centerPosX + halfSideLength * 4, centerPosY - halfSideLength - h2, centerPosZ - halfSideLength * 4, // P4
        centerPosX + halfSideLength * 4, centerPosY - halfSideLength - h2, centerPosZ + halfSideLength * 4  // P6
    };
    GLfloat colour[] = {
        255.0,255.0,255.0,
        255.0,255.0,255.0,
        255.0,255.0,255.0,
        255.0,255.0,255.0,
        
        255.0,255.0,255.0,
        255.0,255.0,255.0,
        255.0,255.0,255.0,
        255.0,255.0,255.0,
        
        255.0,255.0,255.0,
        255.0,255.0,255.0,
        255.0,255.0,255.0,
        255.0,255.0,255.0,
        
        255.0,255.0,255.0,
        255.0,255.0,255.0,
        255.0,255.0,255.0,
        255.0,255.0,255.0,
        
        255.0,255.0,255.0,
        255.0,255.0,255.0,
        255.0,255.0,255.0,
        255.0,255.0,255.0,
        
        255.0,255.0,255.0,
        255.0,255.0,255.0,
        255.0,255.0,255.0,
        255.0,255.0,255.0,
    };
    
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
