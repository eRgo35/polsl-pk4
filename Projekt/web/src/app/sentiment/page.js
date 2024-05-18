import styles from "../page.module.css";

import Header from "../components/Header";
import SideBar from "../components/SideBar";
import SentimentContent from "../components/SentimentContent";
import Footer from "../components/Footer";

export default function Home() {
  return (
    <main className={styles.main}>
      <Header title={"Sentiment Analysis"} path={"sentiment"} />
      <SideBar />
      <SentimentContent />
      {/* <Footer /> */}
    </main>
  );
}
