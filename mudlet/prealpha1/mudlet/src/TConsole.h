/***************************************************************************
 *   Copyright (C) 2008 by Heiko Koehn (KoehnHeiko@googlemail.com)         *
 *                                                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/




#ifndef TCONSOLE_H
#define TCONSOLE_H

//#include <sys/time.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <QMainWindow>
#include <QCloseEvent>
#include "ui_console.h"
#include <QtWebKit>
#include <iostream>
#include "ctelnet.h"
#include "TCommandLine.h"
#include <QPlainTextEdit>
#include <QTextDocumentFragment>
#include "TBuffer.h"

class Host;
class mudlet;
class TTextEdit;
class TBuffer;

class TFontSpecs 
{
public:
    TFontSpecs( Host * pH ){ mpHost = pH; init(); }
    QString getFontWeight()
    { 
        if(bold)
        { 
            return QString("<b>"); 
        }
        else return QString("</b>"); 
    }
    QString getFontStyle(){ return (italics) ? QString("<i>") : QString("</i>");}
    QString getFontDecoration(){ return (underline) ? QString("<u>") : QString("</u>");}
    void init()
    { 
        bold = false;
        italics = false;
        underline = false;
        m_reset = false;
        m_bgColorHasChanged = false;
        m_fgColorHasChanged = false;
        m_bgColorHasChanged_old = false;
        m_fgColorHasChanged_old = false;
        bold_old = false;
        italics_old = false;
        underline_old = false;
        fgColor = mpHost->mFgColor;
        fgColorLight = mpHost->mFgColor;
        bgColor = mpHost->mBgColor;
    }
    void reset()
    {
        init();
    }
    void bg_color_change(){ m_bgColorHasChanged=true; }
    void fg_color_change(){ m_fgColorHasChanged=true; }
    QColor fgColor;
    QColor fgColorLight;
    QColor fgColor_old;
    QColor bgColor;
    QColor bgColor_old;
    bool m_bgColorHasChanged;
    bool m_bgColorHasChanged_old;
    bool m_fgColorHasChanged;
    bool m_fgColorHasChanged_old;
    bool bold;
    bool bold_old;
    bool italics;
    bool italics_old;
    bool underline;
    bool underline_old;
    bool m_reset;
    QString text;
    Host * mpHost;
};



class TConsole : public QWidget 
{
Q_OBJECT

public:
   
                        TConsole( Host *, bool isDebugConsole );
      void              print( QString msg );
      void              printOnDisplay(QString  &);
      void              printCommand( QString & );
      void              echoUserWindow( QString & );
      Host *            getHost() { return mpHost; }
      TCommandLine *    mpCommandLine;
      void              replace( QString );
      void              insertHTML( QString );
      void              insertText( QString );
      void              copy();
      void              cut();
      void              paste();
      void              pasteWindow( QTextDocumentFragment & );
      void              setUserWindow();
      QStringList       getLines( int from, int to );
      int               getLineNumber();
      int               getLineCount();
      void              deleteLine();
      int               getColumnNumber();
      void              setWrapAt( int pos ){ mWrapAt = pos; }
      void              setIndentCount( int count ){ mIndentCount = count; }
      void              echo( QString & );
      bool              moveCursor( int x, int y );
      int               select( QString, int numOfMatch = 1 );
      bool              selectSection( int, int );
      
      void              setFgColor( int, int, int );
      void              setBgColor( int, int, int );
      void              changeColors();
      void              scrollDown( int lines );
      void              scrollUp( int lines );
    
      TTextEdit *       console;
      TTextEdit *       console2;
      int               mUserCursorX;
      int               mUserCursorY;
    
private:
          
      //std::string       getCurrentTime();
      void              toggleCurrentParagraphClosed(bool b)    { m_previousParagraphWasClosed = m_paragraphIsComplete; m_paragraphIsComplete = b; }
      bool              previousParagraphWasClosed()            { return m_previousParagraphWasClosed; }
      void              translateToPlainText( QString & );
      QString           translate( QString & );
      void              set_text_properties( int formatPropertyCode );  
      QString           assemble_html_font_specs();
          
      Host *            mpHost;  
    
      bool              m_pageInitialized;
      QString           mEchoBuffer;
      bool              m_paragraphIsComplete;
      bool              m_previousParagraphWasClosed;
     
      bool              mWaitingForHighColorCode;
      bool              mHighColorModeForeground;
      bool              mHighColorModeBackground;
      bool              mIsHighColorMode;
    
      bool              isUserScrollBack;
      TFontSpecs        m_fontSpecs;
      int               currentFgColorProperty;
      QString           mFormatSequenceRest;
      int               mCursorHome;
      QFont             mDisplayFont;
      QColor            mFgColor;
      QColor            mBgColor;
      bool              mIsDebugConsole;
      int               mWrapAt;
      int               mIndentCount;
      TBuffer           buffer;

signals:
    
    
public slots:    
      
      void              slot_user_scrolling( int );
      
};

#endif

