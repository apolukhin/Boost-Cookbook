function set_cookie(cname, cvalue, exdays) {
    var d = new Date();
    d.setTime(d.getTime() + (exdays*24*60*60*1000));
    var expires = "expires="+ d.toUTCString();
    document.cookie = cname + "=" + cvalue + ";" + expires + ";path=/";
}

function get_cookie(cname) {
    var name = cname + "=";
    var decodedCookie = decodeURIComponent(document.cookie);
    var ca = decodedCookie.split(';');
    for(var i = 0; i <ca.length; i++) {
        var c = ca[i];
        while (c.charAt(0) == ' ') {
            c = c.substring(1);
        }
        if (c.indexOf(name) == 0) {
            return c.substring(name.length, c.length);
        }
    }
    return undefined;
}

function select_language3(language) {
    function default_lang() {
        return (navigator.language || navigator.userLanguage).startsWith("ru") ? "ru" : "en"
    }

    if (language === undefined) {
        language = get_cookie("language");
        if (language === undefined) {
            language = default_lang();
        }
    }

    if (language != "en" && language != "ru") {
        language = default_lang();
    }

    set_cookie("language", language, 31);

    if (language === "ru" && !window.location.href.includes("/ru")) {
        var str = window.location.href;
        var pos = str.lastIndexOf('/');
        str = str.substring(0, pos) + "/ru/" + str.substring(pos + 1);
        window.location = str;    
    } else if (language === "en" && window.location.href.includes("/ru/")) {
        window.location = window.location.href.replace("/ru/", "/");    
    }
}

select_language3()

