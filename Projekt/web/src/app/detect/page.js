import Copyright from "@/components/Copyright";
import { Container, Grid } from "@mui/material";
import DetectForm from './Detect';

export const metadata = {
  title: "Language Detection - NLP Platform"
}

export default function Detect() {

  return (
    <Container maxWidth="lg" sx={{ mt: 4, mb: 4 }}>
      <Grid container spacing={2}>
        <Grid item xs={12}>
          <DetectForm />
        </Grid>
      </Grid>
      <Copyright sx={{ pt: 4 }} />
    </Container>
  );
}