# THE ISS Project
#### Description:
For my final project I've decided to create a website that showed in real time the position of the **International Space Station**.
From this point of view it's a sort of **ISS tracker**. The reason why I chose this topic is that the ISS has always fascinated me and
more importantly, I wanted to use the final project as an opportunity to learn more about **APIs**. As a matter of fact, the ISS website utlizes two different
APIs: the [Open Notify](http://open-notify.org/Open-Notify-API/ISS-Location-Now/) and the [Google Maps API](https://developers.google.com/maps/documentation/javascript/overview).
The former is a simple api to return the current location of the ISS.
It returns the current latitude and longitude of the space station with a unix timestamp for the time the location was valid.

The Maps JavaScript API lets you customize maps with your own content and imagery for display on web pages and mobile devices.
The Maps JavaScript API features four basic map types (roadmap, satellite, hybrid, and terrain),
which you can modify using layers and styles, controls and events, and various services and libraries.

The website is built using:
- Flask
- CSS
- HTML,
- Javascript
- Python

In the homepage I display some basic information about the ISS along some cool photos of the station. A more "complex" HTML structure is the facts container,
which utilizes event listeners and Javascript so to adopt a more dynamic display. It display some trivia and fun facts along some more hardcore facts about the ISS.
The map web page displays the current location of the ISS as per the coordinates obtained by a call to Open Notify API and dynamically displays a map through Maps
JavaScript API.
