import express from 'express';
import cors from 'cors';
import { createRequire } from 'module';

const require = createRequire(import.meta.url);
const rubiks = require('./build/Release/rubiks_addon.node');

const app = express();
app.use(cors());
app.use(express.json());

app.get('/api/scramble', (req, res) => {
  try {
    const raw = rubiks.scramble().trim();
    const moves = raw.split(/\s+/).filter(Boolean);
    res.json({ scramble: raw, moves });
  } catch (err) {
    res.status(500).json({ error: err.message });
  }
});

app.post('/api/solve', (req, res) => {
  try {
    const raw = rubiks.solve().trim();
    const moves = raw.split(/\s+/).filter(Boolean);
    res.json({ solution: raw, moves });
  } catch (err) {
    res.status(500).json({ error: err.message });
  }
});

const PORT = 3001;
app.listen(PORT, () => {
});