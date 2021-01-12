// just like with css we can move our script to a seperate file and then reference it from our html file

function blink()
{
    let h1 = document.querySelector("h1.loop");
    if (h1.style.visibility === 'hidden')
    {
        h1.style.visibility = 'visible';
    }
    else
    {
        h1.style.visibility = 'hidden';
    }
}

// this function let me set an interval to the window so that a function is run every some number of millisecond
// it takes 2 arguments: what function do I want to run and how often I want to run it (in this case every 500 milliseconds)
window.setInterval(blink, 500);
