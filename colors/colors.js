var Box = {
    val: false, 
    index: false,
    mod : function(newVal, i) {  // Method which will display type of Animal
        this.val = newVal;
        this.index = i;
    },
    createHtml : function() {
        var html = "<div id=\"box_" +this.index+ "\" class=\"box";
        if (this.val) {
            html += " isOn";
        }
        html += "\"></div>";
        $('.boxContainer').append(html);
    }
}

var Pattern = {
    graphMode: true,
    x: 0,
    y: 0,
    val: [],
    valString: "",
    generate: function(x, y) {
        this.x = x;
        this.y = y;
        i=0;
        for (x = 1; x <= this.x; x++) { 
            for (y = 1; y <= this.y; y++) {
                var isOn = Math.random()<.5;
                this.val.push(isOn);
                if (this.graphMode) {
                    var box = Object.create(Box);
                    box.mod(isOn, i);
                    box.createHtml();
                }
                i++;
            }
        }
    },
    validate: function() {
        index = 0;
        for (x = 1; x <= this.x; x++) { 
            for (y = 1; y <= this.y; y++) {
                
                if (this.isCenterOfPlus(index)) {
                    $('#box_'+index).addClass('mark');
                    return index;
                }
                
                index++;
            }
        }
    },
    isCenterOfPlus: function(index) {
        if (!this.val[index]) {
            return false;
        }
        if (index < this.x+1) {
            return false;
        }
        if (index > (this.x*this.y)-this.x) {
            return false;
        }
        if (index%this.x == 0) {
            return false;
        }
        if (index%this.x == this.x-1) {
            return false;
        }

        if (!this.val[index-this.x] || !this.val[index+this.x]) {
            return false;
        }
        if (!this.val[index-1] || !this.val[index+1]) {
            return false;
        }
        
        return true;
    },
    write: function() {
        var console = $('#console');
        console.append('in:')
        for (i = 0; i < this.val.length; i++) { 
            if (this.val[i]) {
                console.append('1 ')
            } else {
                console.append('0 ')
            }
        }
        console.append(' out: ')
        if (this.validate()) {
            console.append('1')
        } else {
            console.append('0')
        }
        this.valString = console.html();
    }
}

$(function() {
        function saveLoop() {
            setTimeout(function () {
                
                location.reload();
            }, 300);
        }
    
        pattern = Object.create(Pattern);
        pattern.generate(10, 10);
        console.log(pattern.val);
        console.log(pattern.validate());
        pattern.write();
        
        $.post("http://save.dev", { s: pattern.valString })
        .done(function( data ) {
            console.log(data);
            saveLoop();      
        });
});
