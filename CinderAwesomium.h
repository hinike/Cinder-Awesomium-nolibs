#pragma once

#include <Awesomium/WebCore.h>
#include <Awesomium/BitmapSurface.h>
#include <Awesomium/STLHelpers.h>

#include "cinder/Exception.h"
#include "cinder/Surface.h"
#include "cinder/app/AppBasic.h"
#include "cinder/gl/Texture.h"

namespace ph { namespace awesomium {

// exceptions
class EmptyPointerException : public ci::Exception {
	virtual const char * what() const throw() { return "The specified pointer is empty."; }
};

class InvalidBufferException : public ci::Exception {
	virtual const char * what() const throw() { return "The specified buffer is empty or not initialized."; }
};

// A helper macro, used in 'getWebKeyFromKeyEvent'
#define mapKey(a, b) case ci::app::KeyEvent::KEY_##a: return Awesomium::KeyCodes::AK_##b;

// Translates a Cinder virtual key code to an Awesomium key code
int getWebKeyFromKeyEvent( ci::app::KeyEvent event )
{
    switch( event.getCode() )
    {
    mapKey(BACKSPACE, BACK)
    mapKey(TAB, TAB)
    mapKey(CLEAR, CLEAR)
    mapKey(RETURN, RETURN)
    mapKey(PAUSE, PAUSE)
    mapKey(ESCAPE, ESCAPE)
    mapKey(SPACE, SPACE)
    mapKey(EXCLAIM, 1)
    mapKey(QUOTEDBL, 2)
    mapKey(HASH, 3)
    mapKey(DOLLAR, 4)
    mapKey(AMPERSAND, 7)
    mapKey(QUOTE, OEM_7)
    mapKey(LEFTPAREN, 9)
    mapKey(RIGHTPAREN, 0)
    mapKey(ASTERISK, 8)
    mapKey(PLUS, OEM_PLUS)
    mapKey(COMMA, OEM_COMMA)
    mapKey(MINUS, OEM_MINUS)
    mapKey(PERIOD, OEM_PERIOD)
    mapKey(SLASH, OEM_2)
    mapKey(0, 0)
    mapKey(1, 1)
    mapKey(2, 2)
    mapKey(3, 3)
    mapKey(4, 4)
    mapKey(5, 5)
    mapKey(6, 6)
    mapKey(7, 7)
    mapKey(8, 8)
    mapKey(9, 9)
    mapKey(COLON, OEM_1)
    mapKey(SEMICOLON, OEM_1)
    mapKey(LESS, OEM_COMMA)
    mapKey(EQUALS, OEM_PLUS)
    mapKey(GREATER, OEM_PERIOD)
    mapKey(QUESTION, OEM_2)
    mapKey(AT, 2)
    mapKey(LEFTBRACKET, OEM_4)
    mapKey(BACKSLASH, OEM_5)
    mapKey(RIGHTBRACKET, OEM_6)
    mapKey(CARET, 6)
    mapKey(UNDERSCORE, OEM_MINUS)
    mapKey(BACKQUOTE, OEM_3)
    mapKey(a, A)
    mapKey(b, B)
    mapKey(c, C)
    mapKey(d, D)
    mapKey(e, E)
    mapKey(f, F)
    mapKey(g, G)
    mapKey(h, H)
    mapKey(i, I)
    mapKey(j, J)
    mapKey(k, K)
    mapKey(l, L)
    mapKey(m, M)
    mapKey(n, N)
    mapKey(o, O)
    mapKey(p, P)
    mapKey(q, Q)
    mapKey(r, R)
    mapKey(s, S)
    mapKey(t, T)
    mapKey(u, U)
    mapKey(v, V)
    mapKey(w, W)
    mapKey(x, X)
    mapKey(y, Y)
    mapKey(z, Z)
    mapKey(DELETE, DELETE)
    mapKey(KP0, NUMPAD0)
    mapKey(KP1, NUMPAD1)
    mapKey(KP2, NUMPAD2)
    mapKey(KP3, NUMPAD3)
    mapKey(KP4, NUMPAD4)
    mapKey(KP5, NUMPAD5)
    mapKey(KP6, NUMPAD6)
    mapKey(KP7, NUMPAD7)
    mapKey(KP8, NUMPAD8)
    mapKey(KP9, NUMPAD9)
    mapKey(KP_PERIOD, DECIMAL)
    mapKey(KP_DIVIDE, DIVIDE)
    mapKey(KP_MULTIPLY, MULTIPLY)
    mapKey(KP_MINUS, SUBTRACT)
    mapKey(KP_PLUS, ADD)
    mapKey(KP_ENTER, SEPARATOR)
    mapKey(KP_EQUALS, UNKNOWN)
    mapKey(UP, UP)
    mapKey(DOWN, DOWN)
    mapKey(RIGHT, RIGHT)
    mapKey(LEFT, LEFT)
    mapKey(INSERT, INSERT)
    mapKey(HOME, HOME)
    mapKey(END, END)
    mapKey(PAGEUP, PRIOR)
    mapKey(PAGEDOWN, NEXT)
    mapKey(F1, F1)
    mapKey(F2, F2)
    mapKey(F3, F3)
    mapKey(F4, F4)
    mapKey(F5, F5)
    mapKey(F6, F6)
    mapKey(F7, F7)
    mapKey(F8, F8)
    mapKey(F9, F9)
    mapKey(F10, F10)
    mapKey(F11, F11)
    mapKey(F12, F12)
    mapKey(F13, F13)
    mapKey(F14, F14)
    mapKey(F15, F15)
    mapKey(NUMLOCK, NUMLOCK)
    mapKey(CAPSLOCK, CAPITAL)
    mapKey(SCROLLOCK, SCROLL)
    mapKey(RSHIFT, RSHIFT)
    mapKey(LSHIFT, LSHIFT)
    mapKey(RCTRL, RCONTROL)
    mapKey(LCTRL, LCONTROL)
    mapKey(RALT, RMENU)
    mapKey(LALT, LMENU)
    mapKey(RMETA, LWIN)
    mapKey(LMETA, RWIN)
    mapKey(LSUPER, LWIN)
    mapKey(RSUPER, RWIN)
    mapKey(MODE, MODECHANGE)
    mapKey(COMPOSE, ACCEPT)
    mapKey(HELP, HELP)
    mapKey(PRINT, SNAPSHOT)
    mapKey(SYSREQ, EXECUTE)
    default: return Awesomium::KeyCodes::AK_UNKNOWN;
    }
}

// Conversion functions

ci::Surface toSurface( Awesomium::BitmapSurface* surface )
{
	if( ! surface ) throw EmptyPointerException();
	if( ! surface->buffer() ) throw InvalidBufferException();

	// set isDirty to false, because we are manually copying the data
	surface->set_is_dirty( false );

	// create the Surface by copying the data directly 
	return ci::Surface( (uint8_t*) surface->buffer(), surface->width(), surface->height(), surface->row_span(), ci::SurfaceChannelOrder::BGRA );
}

inline ci::Surface toSurface( Awesomium::WebView* webview )
{
	return toSurface( (Awesomium::BitmapSurface*) webview->surface() );
}

ci::gl::Texture toTexture( Awesomium::BitmapSurface* surface, ci::gl::Texture::Format format=ci::gl::Texture::Format() )
{
	if( ! surface ) throw EmptyPointerException();
	if( ! surface->buffer() ) throw InvalidBufferException();

	// set isDirty to false, because we are manually copying the data
	surface->set_is_dirty( false );

	// create the gl::Texture by copying the data directly
	return ci::gl::Texture( surface->buffer(), GL_BGRA, surface->width(), surface->height(), format );
}

inline ci::gl::Texture toTexture( Awesomium::WebView* webview, ci::gl::Texture::Format format=ci::gl::Texture::Format() )
{
	return toTexture( (Awesomium::BitmapSurface*) webview->surface(), format );
}

inline bool isDirty( Awesomium::WebView* webview ) 
{
	if( ! webview ) throw EmptyPointerException();

	Awesomium::BitmapSurface* surface = (Awesomium::BitmapSurface*) webview->surface();
	if( ! surface ) throw EmptyPointerException();

	return surface->is_dirty();
}

Awesomium::WebKeyboardEvent toKeyDown( ci::app::KeyEvent event )
{
	Awesomium::WebKeyboardEvent evt;
	evt.type = Awesomium::WebKeyboardEvent::kTypeKeyDown;
	evt.virtual_key_code = getWebKeyFromKeyEvent( event );
	evt.native_key_code = event.getNativeKeyCode();
	evt.text[0] = event.getChar();
    evt.unmodified_text[0] = event.getChar();

	char* buf = new char[20];
	Awesomium::GetKeyIdentifierFromVirtualKeyCode(evt.virtual_key_code, &buf);
	strcpy_s<20>(evt.key_identifier, buf);
    delete[] buf;

	// TODO: modifiers

	return evt;
}

Awesomium::WebKeyboardEvent toKeyUp( ci::app::KeyEvent event )
{
	Awesomium::WebKeyboardEvent evt;
	evt.type = Awesomium::WebKeyboardEvent::kTypeKeyUp;
	evt.virtual_key_code = getWebKeyFromKeyEvent( event );
	evt.native_key_code = event.getNativeKeyCode();
	evt.text[0] = event.getChar();
    evt.unmodified_text[0] = event.getChar();

	char* buf = new char[20];
	Awesomium::GetKeyIdentifierFromVirtualKeyCode(evt.virtual_key_code, &buf);
	strcpy_s<20>(evt.key_identifier, buf);
    delete[] buf;

	// TODO: modifiers

	return evt;
}

Awesomium::WebKeyboardEvent toKeyChar( ci::app::KeyEvent event )
{
	Awesomium::WebKeyboardEvent evt;
	evt.type = Awesomium::WebKeyboardEvent::kTypeChar;

	evt.virtual_key_code = event.getChar();
	evt.native_key_code = event.getChar();
	evt.text[0] = event.getChar();
    evt.unmodified_text[0] = event.getChar();

	return evt;
}

// Utility functions that take care of event handling

//! sends a Cinder KeyDown event to the WebView
inline void handleKeyDown( Awesomium::WebView *view, ci::app::KeyEvent event )
{
	view->Focus();
	view->InjectKeyboardEvent( toKeyDown( event ) );
	view->InjectKeyboardEvent( toKeyChar( event ) );
}

//! sends a Cinder KeyUp event to the WebView
inline void handleKeyUp( Awesomium::WebView *view, ci::app::KeyEvent event )
{	
	view->Focus();
	view->InjectKeyboardEvent( toKeyUp( event ) );
}

//! sends a Cinder MouseMove event to the WebView
inline void handleMouseMove( Awesomium::WebView *view, ci::app::MouseEvent event )
{
	view->InjectMouseMove( event.getX(), event.getY() );
}

//! sends a Cinder MouseDown event to the WebView
inline void handleMouseDown( Awesomium::WebView *view, ci::app::MouseEvent event )
{
	if( event.isLeft() )
		view->InjectMouseDown( Awesomium::kMouseButton_Left );
	else if( event.isMiddle() )
		view->InjectMouseDown( Awesomium::kMouseButton_Middle );
	else if( event.isRight() )
		view->InjectMouseDown( Awesomium::kMouseButton_Right );
}

//! sends a Cinder MouseDrag event to the WebView
inline void handleMouseDrag( Awesomium::WebView *view, ci::app::MouseEvent event )
{
	view->InjectMouseMove( event.getX(), event.getY() );
}

//! sends a Cinder MouseUp event to the WebView
inline void handleMouseUp( Awesomium::WebView *view, ci::app::MouseEvent event )
{
	if( event.isLeft() )
		view->InjectMouseUp( Awesomium::kMouseButton_Left );
	else if( event.isMiddle() )
		view->InjectMouseUp( Awesomium::kMouseButton_Middle );
	else if( event.isRight() )
		view->InjectMouseUp( Awesomium::kMouseButton_Right );
}

//! sends a Cinder MouseWheel event to the WebView
inline void handleMouseWheel( Awesomium::WebView *view, ci::app::MouseEvent event, int increment=150 )
{
	view->InjectMouseWheel( increment * int( event.getWheelIncrement() ), 0 );
}

} } // namespace ph::awesomium