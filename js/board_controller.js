/* global JGO:false, WAudio:false */
/* exported BoardController */
// (C) 2017 ICHIKAWA, Yuji (New 3 Rs)

const stoneSound = new WAudio('audio/go-piece1.mp3');

/* jGoBoardのためのコントローラ */
class BoardController {
    constructor(boardSize, color, handicap) {
        this.ownColor = color; // ownColorはGUIを使用する側
        this.turn = JGO.BLACK;
        this.jrecord = null;
        this.jboard = null;
        this.ko = false;
        this.lastHover = null;
        this.lastMove = null;
        this.observers = [];
        this.passNum = 0;

        this.jrecord = new JGO.Record(boardSize);
        this.jboard = this.jrecord.getBoard();
        if (handicap >= 2) {
            const stones = JGO.util.getHandicapCoordinates(this.jboard.width,
                handicap);
            this.jboard.setType(stones, JGO.BLACK);
            this.turn = JGO.WHITE;
        }

        const options = { stars: {points: 9 }};
        JGO.util.extend(options, JGO.BOARD.large);
        const jsetup = new JGO.Setup(this.jboard, options);
        jsetup.setOptions({ coordinates: {
            top: false,
            bottom: false,
            left: false,
            right: false
        }});

        jsetup.create('board', canvas => {
            canvas.addListener('click', this.clickHander.bind(this));
            canvas.addListener('mousemove', this.moveHandler.bind(this));
            canvas.addListener('mouseout', this.leaveHandler.bind(this));
            canvas.addListener('mousedown', this.downHandler.bind(this));
            return;
        });
    }

    addObserver(observer) {
        /**
         * observerは引数にcoordを受け取るupdateメソッドを持つオブジェクト。
         * 追加時とplay直後にupdateを呼び出す。
         */
        this.observers.push(observer);
        observer.update();
    }

    update(coord) {
        const node = this.jrecord.getCurrentNode();
        document.getElementById('black-captures').innerText =
            node.info.captures[JGO.BLACK];
        document.getElementById('white-captures').innerText =
            node.info.captures[JGO.WHITE];
        setTimeout(() => {
            this.observers.forEach(function(observer) {
                observer.update(coord);
            });
        }, 10); // 0ではjGoBoardのレンダリングが終わっていない。
    }

    pass() {
        this.passNum += 1;
        this.turn = this.turn === JGO.BLACK ? JGO.WHITE : JGO.BLACK;
        if (this.passNum < 2) {
            this.update();
        } else {
            // end
        }
    }

    play(coord, sound = false) {
        const play = this.jboard.playMove(coord, this.turn, this.ko);
        if (!play.success) {
            console.log(coord, play);
            return play.success;
        }

        const node = this.jrecord.createNode(false);
        // tally captures
        node.info.captures[this.turn] += play.captures.length;
        // play stone
        node.setType(coord, this.turn);
        // clear opponent's stones
        node.setType(play.captures, JGO.CLEAR);
        if(this.lastMove) {
            node.setMark(this.lastMove, JGO.MARK.NONE); // clear previous mark
        }
        if(this.ko) {
            node.setMark(this.ko, JGO.MARK.NONE); // clear previous ko mark
        }
        node.setMark(coord, JGO.MARK.CIRCLE); // mark move
        this.lastMove = coord;
        if(play.ko) {
            node.setMark(play.ko, JGO.MARK.CIRCLE); // mark ko, too
        }
        this.ko = play.ko;
        this.turn = this.turn === JGO.BLACK ? JGO.WHITE : JGO.BLACK;
        this.passNum = 0;
        this.update(coord);
        if (sound) {
            stoneSound.play();
        }
        return play.success;
    }

    clickHander(coord, ev) {
        // clear hover away - it'll be replaced or
        // then it will be an illegal move in any case
        // so no need to worry about putting it back afterwards
        if (this.ownColor !== this.turn) {
            return;
        }
        if (this.lastHover != null) {
            this.jboard.setType(this.lastHover, JGO.CLEAR);
            this.lastHover = null;
        }
        this.play(coord);
    }

    moveHandler(coord, ev) {
        if (this.ownColor !== this.turn) {
            return;
        }
        if (this.lastHover && this.lastHover.equals(coord)) {
            return;
        }

        if (this.lastHover != null) { // clear previous hover if there was one
            this.jboard.setType(this.lastHover, JGO.CLEAR);
        }

        if (coord.i <= -1 || coord.j <= -1 ||
            coord.i >= this.jboard.width || coord.j >= this.jboard.height) {
            this.lastHover = null;
        } else if (this.jboard.getType(coord) === JGO.CLEAR &&
            this.jboard.getMark(coord) == JGO.MARK.NONE) {
            this.jboard.setType(coord,
                this.turn == JGO.BLACK ? JGO.DIM_BLACK : JGO.DIM_WHITE);
            this.lastHover = coord;
        } else {
            this.lastHover = null;
        }
    }

    leaveHandler(ev) {
        if (this.lastHover != null) {
            this.jboard.setType(this.lastHover, JGO.CLEAR);
            this.lastHover = null;
        }
    }

    downHandler(ev) {
        stoneSound.play();
    }
}
