package cgot

import (
	"bytes"
	"io"
	"path"
	"testing"

	"github.com/rokath/trice/internal/args"
	"github.com/spf13/afero"
	"github.com/tj/assert"
)

func TestLogs(t *testing.T) {
	// triceLog is the log function for executing the trice logging on binary log data in buffer as space separated numbers.
	// It uses the inside fSys specified til.json and returns the log output.
	triceLog := func(t *testing.T, fSys *afero.Afero, buffer string) string {
		var o bytes.Buffer
		assert.Nil(t, args.Handler(io.Writer(&o), fSys, []string{"trice", "log", "-pf=none", "-doubled16BitID", "-i", path.Join(triceDir, "/demoTIL.json"), "-p=BUFFER", "-args", buffer, "-hs=off", "-prefix=off", "-li=off", "-color=none", "-ts0", "Time:        ", "-ts16", "Time:    %04x", "-ts32", "Time:%08x"}))
		return o.String()
	}
	triceLogSpecialTest(t, triceLog, -1)
}
