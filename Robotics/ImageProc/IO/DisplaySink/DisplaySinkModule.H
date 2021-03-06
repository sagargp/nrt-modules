// //////////////////////////////////////////////////////////////////// //
// The NRT iLab Neuromorphic Vision C++ Toolkit, Copyright(C) 2000-2011 //
// by the University of Southern California (USC) and the iLab at USC.  //
// See http://iLab.usc.edu for information about this project.          //
// //////////////////////////////////////////////////////////////////// //
// Portions of the NRT iLab Neuromorphic Vision Toolkit are protected   //
// under the U.S. patent ``Computation of Intrinsic Perceptual Saliency //
// in Visual Environments, and Applications'' by Christof Koch and      //
// Laurent Itti, California Institute of Technology, 2001 (patent       //
// pending; application number 09/912,225 filed July 23, 2001; see      //
// http://pair.uspto.gov/cgi-bin/final/home.pl for current status).     //
// //////////////////////////////////////////////////////////////////// //
// This file is part of the NRT iLab Neuromorphic Vision C++ Toolkit.   //
//                                                                      //
// The NRT iLab Neuromorphic Vision C++ Toolkit is free software; you   //
// can redistribute it and/or modify it under the terms of the GNU      //
// General Public License as published by the Free Software Foundation; //
// either version 2, or (at your option) any later version.             //
//                                                                      //
// The NRT iLab Neuromorphic Vision C++ Toolkit is distributed in the   //
// hope that it will be useful, but WITHOUT ANY WARRANTY; without even  //
// the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR  //
// PURPOSE.  See the GNU General Public License for more details.       //
//                                                                      //
// You should have received a copy of the GNU General Public License    //
// along with the NRT iLab Neuromorphic Vision C++ Toolkit; if not,     //
// write to the Free Software Foundation, Inc., 59 Temple Place, Suite  //
// 330, Boston, MA 02111-1307 USA.                                      //
// //////////////////////////////////////////////////////////////////// //
//
// Primary maintainer for this file: Randolph Voorhies <voorhies@usc.edu>

#ifndef IMAGE_IO_DISPLAYSINK_DISPLAYSINKMODULE_H
#define IMAGE_IO_DISPLAYSINK_DISPLAYSINKMODULE_H

#include <nrt/Core/Blackboard/Module.H>
#include <nrt/Core/Geometry/Point.H>
#include <Messages/ImageProc/GenericImageMessage.H>

namespace nrt{ class DisplayImageSink; }

namespace displaysink
{
  NRT_DECLARE_MESSAGESUBSCRIBER_PORT(Image,     GenericImageMessage,                    void, "Incoming Image");
  NRT_DECLARE_MESSAGEPOSTER_PORT(MouseClick,    nrt::Message<nrt::Point2D<nrt::int32>>, void, "Mouse Click");
  NRT_DECLARE_MESSAGEPOSTER_PORT(KeyboardPress, nrt::Message<nrt::int32>,               void, "Keyboard Press");
  NRT_DECLARE_MESSAGECHECKER_PORT(Label,        nrt::Message<std::string>, "Label to display on the image");
}

//! Displays incoming images in a GTK window
/*! The Display Sink Module subscribes to GenericImageMessages, and will display incoming images in a GTK window. The
    module also posts messages when a user clicks on a displayed Image, or presses a keyboard button when the display
    window is in focus. If there is a message available on the module's Label checker port, then the string contained in
    that message will be pasted on the top-left hand corner of the Image.   
    
    \author Randolph Voorhies
    \keywords display, GUI, GTK, mouse, keyboard */
class DisplaySinkModule: public nrt::Module,
                         public nrt::MessageSubscriber<displaysink::Image>,
                         public nrt::MessageChecker<displaysink::Label>,
                         public nrt::MessagePoster<displaysink::MouseClick,
                                                   displaysink::KeyboardPress>
{
  public:
    DisplaySinkModule(std::string const& instanceid = "");

    void onMessage(displaysink::Image msg);

  private:
    std::shared_ptr<nrt::DisplayImageSink> itsDisplaySink;

    void onMouseClick(nrt::Point2D<nrt::int32> point, nrt::int32 button);
    void onKeyPress(nrt::int32 key);
};

#endif //IMAGE_IO_DISPLAYSINK_DISPLAYSINKMODULE_H
