Configuration
=============

Token Core can be configured by providing one or more optional command-line arguments:
```bash
$ tokencored -setting=value -setting=value
```

All settings can alternatively also be configured via the `bitcoin.conf`.

Depending on the operating system, the default locations for the configuration file are:

- Unix systems: `$HOME/.bitcoin/bitcoin.conf`
- Mac OS X: `$HOME/Library/Application Support/Bitcoin/bitcoin.conf`
- Microsoft Windows: `%APPDATA%/Bitcoin/bitcoin.conf`

A typical `bitcoin.conf` may include:
```
server=1
rpcuser=tokencorerpc
rpcpassword=5hMTZI9iBGFqKxsWfOUF
rpcallowip=127.0.0.1
rpcport=8332
txindex=1
datacarriersize=80
logtimestamps=1
tokendebug=tally
tokendebug=packets
tokendebug=pending
```

## Optional settings

To run and use Token Core, no explicit configuration is necessary.

More information about the general configuration and Bitcoin Core specific options are available in the [Bitcoin wiki](https://en.bitcoin.it/wiki/Running_Bitcoin).

#### General options:

| Name                         | Type         | Default        | Description                                                                     |
|------------------------------|--------------|----------------|---------------------------------------------------------------------------------|
| `startclean`                 | boolean      | `0`            | clear all persistence files on startup; triggers reparsing of Token transactions |
| `tokentxcache`                | number       | `500000`       | the maximum number of transactions in the input transaction cache               |
| `tokenprogressfrequency`      | number       | `30`           | time in seconds after which the initial scanning progress is reported           |
| `tokenseedblockfilter`        | boolean      | `1`            | set skipping of blocks without Token transactions during initial scan            |
| `tokenshowblockconsensushash` | number       | `0`            | calculate and log the consensus hash for the specified block                    |

#### Log options:

| Name                         | Type         | Default        | Description                                                                     |
|------------------------------|--------------|----------------|---------------------------------------------------------------------------------|
| `tokenlogfile`                | string       | `tokencore.log` | the path of the log file (in the data directory per default)                    |
| `tokendebug`                  | multi string | `""`           | enable or disable log categories, can be `"all"`, `"none"`                      |

#### Transaction options:

| Name                         | Type         | Default        | Description                                                                     |
|------------------------------|--------------|----------------|---------------------------------------------------------------------------------|
| `autocommit`                 | boolean      | `1`            | enable or disable broadcasting of transactions, when creating transactions      |
| `datacarrier`                | boolean      | `1`            | if disabled, payloads are embedded multisig, and not in `OP_RETURN` scripts     |
| `datacarriersize`            | number       | `80`           | the maximum size in byte of payloads embedded in `OP_RETURN` scripts            |

**Note:** the options `-datacarrier` and `datacarriersize` affect the global relay policies of transactions with `OP_RETURN` scripts.

#### RPC server options:

| Name                         | Type         | Default        | Description                                                                     |
|------------------------------|--------------|----------------|---------------------------------------------------------------------------------|
| `rpcforceutf8`               | boolean      | `1`            | replace invalid UTF-8 encoded characters with question marks in RPC responses   |

#### User interface options:

| Name                         | Type         | Default        | Description                                                                     |
|------------------------------|--------------|----------------|---------------------------------------------------------------------------------|
| `disclaimer`                 | boolean      | `0`            | explicitly show QT disclaimer on startup                                        |
| `tokenuiwalletscope`          | number       | `65535`        | max. transactions to show in trade and transaction history                      |

#### Alert and activation options:

| Name                         | Type         | Default        | Description                                                                     |
|------------------------------|--------------|----------------|---------------------------------------------------------------------------------|
| `overrideforcedshutdown`     | boolean      | `0`            | overwrite shutdown, triggered by an alert                                       |
| `tokenalertallowsender`       | multi string | `""`           | whitelist senders of alerts, can be `"any"`                                     |
| `tokenalertignoresender`      | multi string | `""`           | ignore senders of alerts                                                        |
| `tokenactivationallowsender`  | multi string | `""`           | whitelist senders of activations                                                |
| `tokenactivationignoresender` | multi string | `""`           | ignore senders of activations                                                   |

**Note:** alert and activation related options are consensus affecting and should only be used for tests or under exceptional circumstances!
