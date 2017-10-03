/* global JGO:false, $:false */
/* global GoPosition:false, BoardController:false */
// (C) 2017 ICHIKAWA, Yuji (New 3 Rs)

function softMaxCPU(vec) {
  let max = vec.reduce((max, v) => Math.max(max, v))

  let expDelta = vec.map(v => Math.exp(v - max));
  let sumExpDelta = expDelta.reduce((sum, e) => sum + e);
  let result = expDelta.map(e => e / sumExpDelta);

  return result;
}

class PlayController {
    constructor(model, cnn, board) {
        this.model = model;
        this.cnn = cnn;
        this.board = board;
    }

    async update(coord) {
        if (coord) {
            this.model.play(this.model.xyToPoint(coord.i + 1, coord.j + 1));
        }
        if (this.board.turn !== this.board.ownColor) {
            //console.log(this.model.toString());
            //alert();
            const start = Date.now();
            const feature = this.model.getFeatures();
            //console.log(feature.toString());
            this.cnn.getInputViews()[0].set(feature.transpose());
            await this.cnn.run();
            let output = this.cnn.getOutputViews()[0].toActual();
            if (this.cnn.backendName === 'webgl') {
                output = softMaxCPU(output);
            }
            console.log(Date.now() - start);
            console.log(output);
            const xy = this.selectMove(output, feature);
            //console.log(xy);
            if (xy) {
                this.board.play(new JGO.Coordinate(xy[0] - 1, xy[1] - 1));
            } else {
                this.board.pass();
            }
        }
    }

    selectMove(distribution, feature) {
        if (feature.noSensible) {
            return null;
        }
        let xy;
        let probability;
        do {
            const random = Math.random();
            let accu = 0.0;
            let i;
            for (i = 0; i < distribution.length; i++) {
                accu += distribution[i];
                if (accu > random) {
                    probability = distribution[i];
                    break;
                }
            }
            if (i >= distribution.length) {
                continue;
            }
            const yx = this.model.pointToXy(i);
            // distributionのアラインメントが転置している(tf仕様)ので下でx,yを逆にする。
            xy = [yx[1], yx[0]];
        } while (!feature.getFeature(46, xy[0], xy[1])); // sensibleness

        console.log(probability);
        /*
        console.log(feature.planeToString(0));
        console.log(feature.planeToString(1));
        console.log(feature.planeToString(46));
        */
        return xy;
    }
}

const cnnPromise = WebDNN.load('./WebDNN/output', {
    backendOrder: ['webgpu', 'webgl', 'webassembly']
});

const conditionPromise = new Promise(function(res, rej) {
    const $startModal = $('#start-modal');
    $startModal.modal('show');
    $startModal.on('hidden.bs.modal', function(e) {
        const $conditionForm = $('#condition-form');
        res({
            color: $conditionForm[0].color.value,
            handicap: $conditionForm[0].handicap.value
        });
    });
});

Promise.all([cnnPromise, conditionPromise]).then(function(data) {
    const cnn = data[0];
    console.log(cnn.backendName);
    const color = data[1].color === 'B' ? JGO.BLACK : JGO.WHITE;
    const handicap = parseInt(data[1].handicap);
    const model = new GoPosition(19, handicap);
    const board = new BoardController(19, color, handicap);
    const controller = new PlayController(model, cnn, board);
    board.addObserver(controller);
})
