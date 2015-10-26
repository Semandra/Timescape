// Customization patch of Similie-timeline 2.4.1
// Reverse customizations based on mnosal code here: https://groups.google.com/forum/#!topic/simile-widgets/zNYGSLwwHW4

console.log("I've loaded the patch");
console.log(Timeline);
Timeline.REVERSE=0;
Timeline.FORWARD=1;

// Replace current function in timeline-bundle.js for direction of entry control
Timeline.createBandInfo = function(params) {
    var theme = ("theme" in params) ? params.theme : Timeline.getDefaultTheme();
    var decorators = ("decorators" in params) ? params.decorators : [];
    var eventSource = ("eventSource" in params) ? params.eventSource : null;
    var ether = new Timeline.LinearEther({
        centersOn: ("date" in params) ? params.date : new Date(),
        interval: SimileAjax.DateTime.gregorianUnitLengths[params.intervalUnit],
        pixelsPerInterval: params.intervalPixels,
        theme: theme
    });
    var etherPainter = new Timeline.GregorianEtherPainter({
        unit: params.intervalUnit,
        multiple: ("multiple" in params) ? params.multiple : 1,
        theme: theme,
        align: ("align" in params) ? params.align : undefined
    });
    var eventPainterParams = {
        showText: ("showEventText" in params) ? params.showEventText : true,
		direction : ("direction" in params) ? params.direction : Timeline.REVERSE, //Semandra - add direction parameter
        theme: theme
    };
    if ("eventPainterParams" in params) {
        for (var prop in params.eventPainterParams) {
            eventPainterParams[prop] = params.eventPainterParams[prop];
        }
    }
    if ("trackHeight" in params) {
        eventPainterParams.trackHeight = params.trackHeight;
    }
    if ("trackGap" in params) {
        eventPainterParams.trackGap = params.trackGap;
    }
    var layout = ("overview" in params && params.overview) ? "overview" : ("layout" in params ? params.layout : "original");
    var eventPainter;
    if ("eventPainter" in params) {
        eventPainter = new params.eventPainter(eventPainterParams);
    } else {
        switch (layout) {
            case "overview":
                eventPainter = new Timeline.OverviewEventPainter(eventPainterParams);
                break;
            case "detailed":
                eventPainter = new Timeline.DetailedEventPainter(eventPainterParams);
                break;
            default:
                eventPainter = new Timeline.OriginalEventPainter(eventPainterParams);
        }
    }
    return {
        width: params.width,
        eventSource: eventSource,
        timeZone: ("timeZone" in params) ? params.timeZone : 0,
        ether: ether,
        etherPainter: etherPainter,
        eventPainter: eventPainter,
        theme: theme,
        decorators: decorators,
        zoomIndex: ("zoomIndex" in params) ? params.zoomIndex : 0,
        zoomSteps: ("zoomSteps" in params) ? params.zoomSteps : null
    };
};

// Replace current function in timeline-bundle.js
// Customizations added to support reverse tape display (left to right)

Timeline.createHotZoneBandInfo = function(params) {
    var theme = ("theme" in params) ? params.theme : Timeline.getDefaultTheme();
    var eventSource = ("eventSource" in params) ? params.eventSource : null;
    var ether = new Timeline.HotZoneEther({
        centersOn: ("date" in params) ? params.date : new Date(),
        interval: SimileAjax.DateTime.gregorianUnitLengths[params.intervalUnit],
        pixelsPerInterval: params.intervalPixels,
        zones: params.zones,
        theme: theme
    });
    var etherPainter = new Timeline.HotZoneGregorianEtherPainter({
        unit: params.intervalUnit,
        zones: params.zones,
        theme: theme,
        align: ("align" in params) ? params.align : undefined
    });
    var eventPainterParams = {
        showText: ("showEventText" in params) ? params.showEventText : true,
		direction : ("direction" in params) ? params.direction : Timeline.REVERSE, //Semandra - add direction parameter
        theme: theme
    };
    if ("eventPainterParams" in params) {
        for (var prop in params.eventPainterParams) {
            eventPainterParams[prop] = params.eventPainterParams[prop];
        }
    }
    if ("trackHeight" in params) {
        eventPainterParams.trackHeight = params.trackHeight;
    }
    if ("trackGap" in params) {
        eventPainterParams.trackGap = params.trackGap;
    }
    var layout = ("overview" in params && params.overview) ? "overview" : ("layout" in params ? params.layout : "original");
    var eventPainter;
    if ("eventPainter" in params) {
        eventPainter = new params.eventPainter(eventPainterParams);
    } else {
        switch (layout) {
            case "overview":
                eventPainter = new Timeline.OverviewEventPainter(eventPainterParams);
                break;
            case "detailed":
                eventPainter = new Timeline.DetailedEventPainter(eventPainterParams);
                break;
            default:
                eventPainter = new Timeline.OriginalEventPainter(eventPainterParams);
        }
    }
    return {
        width: params.width,
        eventSource: eventSource,
        timeZone: ("timeZone" in params) ? params.timeZone : 0,
        ether: ether,
        etherPainter: etherPainter,
        eventPainter: eventPainter,
        theme: theme,
        zoomIndex: ("zoomIndex" in params) ? params.zoomIndex : 0,
        zoomSteps: ("zoomSteps" in params) ? params.zoomSteps : null
    };
};

// Replace current function in timeline-bundle.js
// Adds extra classes in tapes for more advanced formatting

Timeline.OriginalEventPainter.prototype._paintEventTape = function(evt, iconTrack, startPixel, endPixel, color, opacity, metrics, theme, tape_index) {
    //var tapeWidth = endPixel - startPixel;
	var tapeWidth = endPixel - startPixel + 5; //Semandra - add space to tape width
	var tapeWidth = endPixel - startPixel
    var tapeHeight = theme.event.tape.height;
    var top = metrics.trackOffset + iconTrack * metrics.trackIncrement;
    var tapeDiv = this._timeline.getDocument().createElement("div");
    
	// Semandra -- create tapeClass variable to add additional styles
	var tapeClass = "tapeLayer" + tape_index + " ";
    if (evt._start == evt._latestStart) {
        tapeClass = tapeClass + "startKnown ";
    }
    if (evt._end == evt._earliestEnd) {
        tapeClass = tapeClass + "endKnown ";
    }
    if (evt._instant == true) {
        tapeClass = tapeClass + "singleDateEvent";
    }
	
	
	//tapeDiv.className = this._getElClassName("timeline-event-tape", evt, "tape");
	tapeDiv.className = this._getElClassName("timeline-event-tape " + tapeClass, evt, "tape"); //Semandra - add class between tape 
	
    tapeDiv.id = this._encodeEventElID("tape" + tape_index, evt);
    tapeDiv.style.left = startPixel + "px";
    tapeDiv.style.width = tapeWidth + "px";
    tapeDiv.style.height = tapeHeight + "px";
    tapeDiv.style.top = top + "px";
    if (evt._title != null) {
        tapeDiv.title = evt._title;
    }
    if (color != null) {
        tapeDiv.style.backgroundColor = color;
    }
    var backgroundImage = evt.getTapeImage();
    var backgroundRepeat = evt.getTapeRepeat();
    backgroundRepeat = backgroundRepeat != null ? backgroundRepeat : "repeat";
    if (backgroundImage != null) {
        tapeDiv.style.backgroundImage = "url(" + backgroundImage + ")";
        tapeDiv.style.backgroundRepeat = backgroundRepeat;
    }
    SimileAjax.Graphics.setOpacity(tapeDiv, opacity);
    this._eventLayer.appendChild(tapeDiv);
    return {
        left: startPixel,
        top: top,
        width: tapeWidth,
        height: tapeHeight,
        elmt: tapeDiv
    };
};

// Replace current function in timeline-bundle.js
Timeline.DefaultEventSource.Event.prototype = {
    getID: function() {
        return this._id;
    },
    isInstant: function() {
        return this._instant;
    },
    isImprecise: function() {
        return this._start != this._latestStart || this._end != this._earliestEnd;
    },
    getStart: function() {
        return this._start;
    },
    getEnd: function() {
        return this._end;
    },
    getLatestStart: function() {
        return this._latestStart;
    },
    getEarliestEnd: function() {
        return this._earliestEnd;
    },
    getEventID: function() {
        return this._eventID;
    },
    getText: function() {
        return this._text;
    },
    getDescription: function() {
        return this._description;
    },
    getImage: function() {
        return this._image;
    },
    getLink: function() {
        return this._link;
    },
    getIcon: function() {
        return this._icon;
    },
    getColor: function() {
        return this._color;
    },
    getTextColor: function() {
        return this._textColor;
    },
    getClassName: function() {
        return this._classname;
    },
    getTapeImage: function() {
        return this._tapeImage;
    },
    getTapeRepeat: function() {
        return this._tapeRepeat;
    },
    getTrackNum: function() {
        return this._trackNum;
    },
    getProperty: function(name) {
        return null;
    },
    getWikiURL: function() {
        return this._wikiURL;
    },
    getWikiSection: function() {
        return this._wikiSection;
    },
    setWikiInfo: function(wikiURL, wikiSection) {
        this._wikiURL = wikiURL;
        this._wikiSection = wikiSection;
    },
    fillDescription: function(elmt) {
        if (this._description) {
            elmt.innerHTML = this._description;
        }
    },
    fillWikiInfo: function(elmt) {
        elmt.style.display = "none";
        if (this._wikiURL == null || this._wikiSection == null) {
            return;
        }
        var wikiID = this.getProperty("wikiID");
        if (wikiID == null || wikiID.length == 0) {
            wikiID = this.getText();
        }
        if (wikiID == null || wikiID.length == 0) {
            return;
        }
        elmt.style.display = "inline";
        wikiID = wikiID.replace(/\s/g, "_");
        var url = this._wikiURL + this._wikiSection.replace(/\s/g, "_") + "/" + wikiID;
        var a = document.createElement("a");
        a.href = url;
        a.target = "new";
        a.innerHTML = Timeline.strings[Timeline.clientLocale].wikiLinkLabel;
        
		// Semandra removed - Creates discuss link in popup bubble
		// elmt.appendChild(document.createTextNode("["));
		// elmt.appendChild(a);
		// elmt.appendChild(document.createTextNode("]"));
    },
    fillTime: function(elmt, labeller) {
        // REMOVED in favour of using a user field "displayDate"	--  Semandra
		/*if (this._instant) {
            if (this.isImprecise()) {
                elmt.appendChild(elmt.ownerDocument.createTextNode(labeller.labelPrecise(this._start)));
                elmt.appendChild(elmt.ownerDocument.createElement("br"));
                elmt.appendChild(elmt.ownerDocument.createTextNode(labeller.labelPrecise(this._end)));
            } else {
                elmt.appendChild(elmt.ownerDocument.createTextNode(labeller.labelPrecise(this._start)));
            }
        } else {
            if (this.isImprecise()) {
                elmt.appendChild(elmt.ownerDocument.createTextNode(labeller.labelPrecise(this._start) + " ~ " + labeller.labelPrecise(this._latestStart)));
                elmt.appendChild(elmt.ownerDocument.createElement("br"));
                elmt.appendChild(elmt.ownerDocument.createTextNode(labeller.labelPrecise(this._earliestEnd) + " ~ " + labeller.labelPrecise(this._end)));
            } else {
                elmt.appendChild(elmt.ownerDocument.createTextNode(labeller.labelPrecise(this._start)));
                elmt.appendChild(elmt.ownerDocument.createElement("br"));
                elmt.appendChild(elmt.ownerDocument.createTextNode(labeller.labelPrecise(this._end)));
            }
        }*/
		
		// New display date that shows in popup bubble
		var dateStart = new Date(labeller.labelPrecise(this._start));
        var dateLatestStart = new Date(labeller.labelPrecise(this._latestStart));
        var dateEarlyEnd = new Date(labeller.labelPrecise(this._earliestEnd));
        var dateEnd = new Date(labeller.labelPrecise(this._end));
		
		console.log(dateStart);
		console.log(dateLatestStart);
		console.log(dateEarlyEnd);
		console.log(dateEnd);
        console.log(this._obj.displayDate);

        dateStart = dateStart.format('mmm d, yyyy');
        dateLatestStart = dateLatestStart.format('mmm d, yyyy');
        dateEarlyEnd = dateEarlyEnd.format('mmm d, yyyy');
        dateEnd = dateEnd.format('mmm d, yyyy');
		
		// displayDate is pulled from a data field
        // elmt.appendChild(elmt.ownerDocument.createTextNode(this._obj.displayDate));
		
    },
    fillInfoBubble: function(elmt, theme, labeller) {
        var doc = elmt.ownerDocument;
        var title = this.getText();
        var link = this.getLink();
        var image = this.getImage();
        if (image != null) {
            var img = doc.createElement("img");
            img.src = image;
            theme.event.bubble.imageStyler(img);
            elmt.appendChild(img);
        }
        var divTitle = doc.createElement("div");
        var textTitle = doc.createTextNode(title);
        if (link != null) {
            var a = doc.createElement("a");
            a.href = link;
            a.appendChild(textTitle);
            divTitle.appendChild(a);
        } else {
            divTitle.appendChild(textTitle);
        }
        theme.event.bubble.titleStyler(divTitle);
        elmt.appendChild(divTitle);
        var divBody = doc.createElement("div");
        this.fillDescription(divBody);
        theme.event.bubble.bodyStyler(divBody);
        elmt.appendChild(divBody);
        var divTime = doc.createElement("div");
        this.fillTime(divTime, labeller);
        theme.event.bubble.timeStyler(divTime);
        elmt.appendChild(divTime);
        var divWiki = doc.createElement("div");
        this.fillWikiInfo(divWiki);
        theme.event.bubble.wikiStyler(divWiki);
        elmt.appendChild(divWiki);
    }
};