'use strict';

var path = require('path');

const CdrPlugin = require(path.join(global.CDR_INSTALL_DIR, '/commander/classes/CdrPlugin')).CdrPlugin;

module.exports = class CfeCdrPlugin extends CdrPlugin {
  constructor(urlBase) {
    super(path.basename(__dirname), path.join(__dirname, 'web', urlBase));
  }

  getContent() {
    var result = {
      shortDescription: 'Actuator and Motor Control',
      longDescription: 'Actuator and Motor Control.',
      nodes: {
				main: {
					type: CdrPlugin.ContentType.LAYOUT,
					shortDescription: 'Main',
					longDescription: 'Main AMC.',
					filePath: '/main_layout.lyt'
				},
				appctrl: {
					type: CdrPlugin.ContentType.PANEL,
					shortDescription: 'Application Control',
					longDescription: 'Application start, stop, restart, and reload.',
					filePath: '/appctrl.pug'
				},
				cdh: {
					type: CdrPlugin.ContentType.PANEL,
					shortDescription: 'Command and Data Handling',
					longDescription: 'Command counters.',
					filePath: '/cdh.pug'
				},
				version: {
					type: CdrPlugin.ContentType.PANEL,
					shortDescription: 'Version',
					longDescription: 'Core versions.',
					filePath: '/version.pug'
				}
      }
    };

    return result;
  }
};

//var plugin = new CfeCdrPlugin();

//let CfeCdrPlugin = new class extends CdrPlugin {
